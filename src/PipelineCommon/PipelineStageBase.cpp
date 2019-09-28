#include "PipelineStageBase.hpp"

#include <chrono>
#include <thread>

#include "PipelineDataBase.hpp"
#include "IDataProcessor.hpp"
#include "IMessageRouter.hpp"
#include "PipelineShutdownMessage.hpp"

using std::make_unique;
using std::thread;
using std::unique_lock;
using std::unique_ptr;
using std::chrono::seconds;
using std::this_thread::sleep_for;

namespace pipeline
{
PipelineStageBase::PipelineStageBase(uint32_t thisComponentId, uint32_t componentLinkType,
                                     IDataProcessor* pDataProcessor, IMessageRouter* pMessageRouter)
    : thisComponentId_(thisComponentId),
      componentLinkType_(componentLinkType),
      bThreadIsRunning_(false),
      bThreadHasJoined_(false),
      pDataProcessor_(pDataProcessor),
      pMessageRouter_(pMessageRouter)
{
}

PipelineStageBase::~PipelineStageBase()
{
    // TODO
}

void PipelineStageBase::runComponent()
{
    if (!bThreadIsRunning_ && pMessageRouter_ != nullptr)
    {
        pMessageRouter_->registerComponent(thisComponentId_, componentLinkType_);

        dataProcessorThread_ = thread(&PipelineStageBase::incomingMessageThread, this);

        // wait for thread to start
        while (!bThreadIsRunning_)
            ;
    }
}

void PipelineStageBase::stopComponent() { doStopStage(); }

bool PipelineStageBase::isComponentRunning() const noexcept { return bThreadIsRunning_; }

void PipelineStageBase::incomingMessageThread()
{
    bThreadIsRunning_ = true;

    while (bThreadIsRunning_)
    {
        // don't need to check if pMessageRouter_ is a nullptr since this method (thread) can't be
        // called/started if it's a nullptr
        auto pReceivedMessage = pMessageRouter_->receiveMessage(thisComponentId_);

        if (pReceivedMessage != nullptr)
        {
            // check if message is destined to this stage
            // if not, drop the message
            if (pReceivedMessage->getDestination() == thisComponentId_)
            {
                switch (pReceivedMessage->getMessageType())
                {
                    case MessageType::MESSAGE_TYPE_PIPELINE_DATA:
                        pDataProcessor_->processMessage(pReceivedMessage);
                        pMessageRouter_->sendMessage(pReceivedMessage);
                        break;

                    case MessageType::MESSAGE_TYPE_SHUTDOWN:
                        bThreadIsRunning_ = false;
                        break;

                    default:
                        break;
                }
            }
        }
    }

    bThreadIsRunning_ = false;
}

void PipelineStageBase::doStopStage()
{
    if (pMessageRouter_ != nullptr)
    {
        // create a PipelineShutdownMessage and send to itself
        unique_ptr<PipelineMessageBase> pPipelineShutdownMessage =
            make_unique<PipelineShutdownMessage>(thisComponentId_, thisComponentId_, 0);
        pMessageRouter_->sendMessage(pPipelineShutdownMessage);
    }
    else
    {
        bThreadIsRunning_ = false;
    }

    if (!bThreadHasJoined_)
    {
        while (!dataProcessorThread_.joinable())
            ;

        dataProcessorThread_.join();

        bThreadHasJoined_ = true;
    }
}

}  // namespace pipeline
