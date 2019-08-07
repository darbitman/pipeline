#include "PipelineMessageRouter.hpp"

#include <memory>
#include <thread>

#include "PipelineSenderReceiver.hpp"

using std::shared_ptr;
using std::thread;

namespace sc
{
PipelineMessageRouter::PipelineMessageRouter(shared_ptr<PipelineSenderReceiver> pSenderReceiver,
                                             std::shared_ptr<PipelineQueueManager> pQueueManager)
    : bInitialized_(false),
      thisStageId_(PipelineStage::MESSAGE_ROUTER),
      bRunReceiverThread_(false),
      bReceiverThreadShutdown_(true),
      pSenderReceiver_(pSenderReceiver),
      pQueueManager_(pQueueManager)
{
    registerNewStage(thisStageId_, PipelineQueueTypes::QUEUE_TYPE_FIFO);
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

bool PipelineMessageRouter::isInitialized() const { return bInitialized_; }

void PipelineMessageRouter::registerNewStage(int32_t stageId, int32_t queueType)
{
    if (stageIdToQueueIdMap_.count(stageId) != 0)
    {
        stageIdToQueueIdMap_[stageId] = pQueueManager_->createNewQueue(queueType);
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
            auto pReceivedMessage = pSenderReceiver_->receive(thisStageId_);

            if (pReceivedMessage != nullptr)
            {
                auto receivedMessageType = pReceivedMessage->getMessageType();

                auto messageDestination = pReceivedMessage->getDestination();

                if (messageDestination != thisStageId_)
                {
                    forwardMessage(pReceivedMessage);
                }
                else
                {
                    if (receivedMessageType == EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA)
                    {
                        // TODO process data
                    }
                    else if (receivedMessageType == EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN)
                    {
                        bRunReceiverThread_ = false;
                        // TODO process shutdown message
                        // if message destination is router, then shut router down and forward
                        // message to ALL stages
                    }
                    else
                    {
                        // TODO handle other message
                    }
                }
            }
        }
    }

    bReceiverThreadShutdown_ = true;
}

void PipelineMessageRouter::forwardMessage(shared_ptr<BasePipelineMessage> pMessage)
{
    auto pQueue = pQueueManager_->getQueue(pMessage->getDestination());

    if (pQueue != nullptr)
    {
        pQueue->push(pMessage);
    }
}
}  // namespace sc
