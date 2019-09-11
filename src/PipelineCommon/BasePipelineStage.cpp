#include "BasePipelineStage.hpp"

#include <chrono>
#include <thread>

#include "BasePipelineData.hpp"
#include "ShutdownMessage.hpp"

using std::make_unique;
using std::thread;
using std::unique_lock;
using std::unique_ptr;
using std::chrono::seconds;
using std::this_thread::sleep_for;

namespace sc
{
BasePipelineStage::BasePipelineStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                                     PipelineSenderReceiver* pSenderReceiver)
    : thisStageId_(thisStageId),
      queueType_(queueType),
      bThreadIsRunning_(false),
      bIsInitialized_(false),
      bThreadHasJoined_(false),
      pSenderReceiver_(pSenderReceiver)
{
}

BasePipelineStage::~BasePipelineStage() {}

void BasePipelineStage::initialize()
{
    if (bIsInitialized_ == false && pSenderReceiver_ != nullptr)
    {
        pSenderReceiver_->registerNewStage(thisStageId_, queueType_);
        bIsInitialized_ = true;
    }
}

void BasePipelineStage::runStage()
{
    if (bIsInitialized_ && !bThreadIsRunning_)
    {
        processingThread_ = thread(&BasePipelineStage::runThread, this);

        // wait for thread to start
        while (!bThreadIsRunning_)
            ;
    }
}

void BasePipelineStage::stopStage() { doStopStage(); }

bool BasePipelineStage::isInitialized() const { return bIsInitialized_; }

bool BasePipelineStage::isRunning() const { return bThreadIsRunning_; }

void BasePipelineStage::runThread()
{
    bThreadIsRunning_ = true;

    while (bThreadIsRunning_)
    {
        // don't need to check if pSenderReceiver_ is a nullptr since this method (thread) can't be
        // called/started if it's a nullptr
        auto pReceivedMessage = pSenderReceiver_->receive(thisStageId_);

        if (pReceivedMessage != nullptr)
        {
            // check if message is destined to this stage
            // if not, drop the message
            if (pReceivedMessage->getDestination() == thisStageId_)
            {
                switch (pReceivedMessage->getMessageType())
                {
                    case EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA:
                        processMessage(pReceivedMessage);
                        pSenderReceiver_->send(pReceivedMessage);
                        break;

                    case EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN:
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

void BasePipelineStage::doStopStage()
{
    if (pSenderReceiver_ != nullptr)
    {
        // create a ShutdownMessage and send to itself
        unique_ptr<BasePipelineMessage> pShutdownMessage =
            make_unique<ShutdownMessage>(thisStageId_, thisStageId_, 0);
        pSenderReceiver_->send(pShutdownMessage);
    }
    else
    {
        bThreadIsRunning_ = false;
    }

    if (!bThreadHasJoined_)
    {
        while (!processingThread_.joinable())
            ;

        processingThread_.join();

        bThreadHasJoined_ = true;
    }

    if (bIsInitialized_)
    {
        bIsInitialized_ = false;
    }
}

}  // namespace sc
