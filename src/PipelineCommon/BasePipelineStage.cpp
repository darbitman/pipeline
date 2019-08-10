#include "BasePipelineStage.hpp"

#include <thread>

#include "BasePipelineData.hpp"
#include "ShutdownMessage.hpp"

using std::make_shared;
using std::shared_ptr;
using std::thread;
using std::unique_lock;

namespace sc
{
BasePipelineStage::BasePipelineStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                                     shared_ptr<PipelineSenderReceiver> pSenderReceiver)
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
        bThreadIsRunning_ = true;
        thread(&BasePipelineStage::runThread, this).detach();
    }
}

void BasePipelineStage::stopStage() { doStopStage(); }

bool BasePipelineStage::isInitialized() const { return bIsInitialized_; }

bool BasePipelineStage::isRunning() const { return bThreadIsRunning_; }

void BasePipelineStage::runThread()
{
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
                    processData(pReceivedMessage->getPipelineData());
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
    shared_ptr<BasePipelineMessage> pShutdownMessage = make_shared<ShutdownMessage>(thisStageId_);
    pSenderReceiver_->send(pShutdownMessage);
}

void BasePipelineStage::processData(shared_ptr<BasePipelineData> pData)
{
    // DEFINE IN DERIVED CLASS
}
}  // namespace sc
