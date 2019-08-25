#include "BasePipelineStage.hpp"

#include <thread>

#include "BasePipelineData.hpp"
#include "ShutdownMessage.hpp"

using std::make_unique;
using std::thread;
using std::unique_lock;
using std::unique_ptr;

namespace sc
{
BasePipelineStage::BasePipelineStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                                     PipelineSenderReceiver* pSenderReceiver)
    : thisStageId_(thisStageId),
      queueType_(queueType),
      bThreadIsRunning_(false),
      bIsInitialized_(false),
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
        thread(&BasePipelineStage::runThread, this).detach();

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
        auto pReceivedMessage = pSenderReceiver_->receive(thisStageId_);

        if (pReceivedMessage != nullptr)
        {
            // check if message is destined to this stage
            if (pReceivedMessage->getDestination() == thisStageId_)
            {
                if (pReceivedMessage->getMessageType() ==
                    EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA)
                {
                    processMessage(pReceivedMessage);

                    pSenderReceiver_->send(pReceivedMessage);
                }
                else if (pReceivedMessage->getMessageType() ==
                         EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN)
                {
                    bThreadIsRunning_ = false;
                }
            }
        }
    }

    bThreadIsRunning_ = false;
}

void BasePipelineStage::doStopStage()
{
    // create a ShutdownMessage and send to itself
    unique_ptr<BasePipelineMessage> pShutdownMessage = make_unique<ShutdownMessage>(thisStageId_);
    pSenderReceiver_->send(pShutdownMessage);
}

}  // namespace sc
