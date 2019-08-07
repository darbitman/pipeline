#include "PipelineSenderReceiver.hpp"

#include <memory>

using std::shared_ptr;

namespace sc
{
PipelineSenderReceiver::PipelineSenderReceiver(shared_ptr<PipelineQueueManager> pQueueManager)
    : pQueueManager_(pQueueManager)
{
}

PipelineSenderReceiver::~PipelineSenderReceiver() {}

bool PipelineSenderReceiver::send(shared_ptr<BasePipelineMessage> dataToSend)
{
    auto pQueue = pQueueManager_->getQueue(PipelineStage::MESSAGE_ROUTER);

    if (pQueue != nullptr)
    {
        pQueue->push(dataToSend);
    }
}

shared_ptr<BasePipelineMessage> PipelineSenderReceiver::receive(int32_t currentStageId)
{
    auto pQueue = pQueueManager_->getQueue(currentStageId);

    if (pQueue != nullptr)
    {
        auto pReceivedMessage = pQueue->front();
        pQueue->pop();
        return pReceivedMessage;
    }
    else
    {
        return nullptr;
    }
}
}  // namespace sc