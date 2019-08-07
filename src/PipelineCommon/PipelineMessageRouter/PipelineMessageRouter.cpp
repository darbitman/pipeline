#include "PipelineMessageRouter.hpp"

#include <memory>
#include <thread>

#include "PipelineSenderReceiver.hpp"

using std::shared_ptr;
using std::thread;

namespace sc
{
PipelineMessageRouter::PipelineMessageRouter(shared_ptr<PipelineSenderReceiver> pSenderReceiver,
                                             int32_t thisStage)
    : bInitialized_(false),
      thisStage_(thisStage),
      bRunReceiverThread_(false),
      bReceiverThreadShutdown_(true),
      pSenderReceiver_(pSenderReceiver)
{
}

PipelineMessageRouter::~PipelineMessageRouter() {}

void PipelineMessageRouter::initialize()
{
    if (!bInitialized_ && pSenderReceiver_ != nullptr)
    {
        thread(&PipelineMessageRouter::receiverThread, this).detach();

        bInitialized_ = true;
    }
}

void PipelineMessageRouter::receiverThread()
{
    bRunReceiverThread_ = true;
    bReceiverThreadShutdown_ = false;

    while (bRunReceiverThread_)
    {
        if (pSenderReceiver_ != nullptr)
        {
            auto pReceivedMessage = pSenderReceiver_->receive(thisStage_);

            if (pReceivedMessage != nullptr)
            {
                auto receivedMessageType = pReceivedMessage->getMessageType();

                auto messageDestination = pReceivedMessage->getDestination();

                if (receivedMessageType == EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA)
                {
                    // TODO process data
                }
                else if (receivedMessageType == EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN)
                {
                    // TODO process shutdown message
                    // if message destination is router, then shut router down and forward message
                    // to ALL stages
                    // if message destination is not router, then forward the message to destination
                }
                else if (receivedMessageType ==
                         EPipelineMessageType::MESSAGE_TYPE_REGISTER_WITH_ROUTER)
                {
                    // TODO register new stage with router
                }
                else if (receivedMessageType ==
                         EPipelineMessageType::MESSAGE_TYPE_UNREGISTER_WITH_ROUTER)
                {
                    // TODO unregister stage with router
                }
                else
                {
                    // TODO handle other message
                }
            }
        }
    }
}
}  // namespace sc
