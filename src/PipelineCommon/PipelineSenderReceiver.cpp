#include "PipelineSenderReceiver.hpp"

#include <memory>
#include <thread>

#include "PipelineQueueManager.hpp"

using std::make_shared;
using std::shared_ptr;
using std::thread;

namespace sc
{
PipelineSenderReceiver::PipelineSenderReceiver()
    : bInitialized_(false),
      thisStageId_(EPipelineStageId::MESSAGE_ROUTER),
      bRunReceiverThread_(false),
      bReceiverThreadShutdown_(true)
{
    pQueueManager_ = make_shared<PipelineQueueManager>();
}

PipelineSenderReceiver::~PipelineSenderReceiver() {}

void PipelineSenderReceiver::initialize()
{
    if (!bInitialized_)
    {
        bInitialized_ = true;

        registerNewStage(thisStageId_, EPipelineQueueType::QUEUE_TYPE_FIFO);

        thread(&PipelineSenderReceiver::receiverThread, this).detach();
    }
}

void PipelineSenderReceiver::registerNewStage(EPipelineStageId stageId, EPipelineQueueType queueType)
{
    if (stageIdToQueueIdMap_.count(stageId) == 0)
    {
        stageIdToQueueIdMap_[stageId] = pQueueManager_->createNewQueue(queueType);
    }
}

void PipelineSenderReceiver::unregisterStage(EPipelineStageId stageId)
{
    // TODO
}

bool PipelineSenderReceiver::isStageRegistered(EPipelineStageId stageId)
{
    return (stageIdToQueueIdMap_.count(stageId) > 0);
}

bool PipelineSenderReceiver::isInitialized() const { return bInitialized_; }

bool PipelineSenderReceiver::isShutdown() const { return bReceiverThreadShutdown_; }

bool PipelineSenderReceiver::send(shared_ptr<BasePipelineMessage> dataToSend)
{
    if (stageIdToQueueIdMap_.count(thisStageId_) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(thisStageId_);
        auto pQueue = pQueueManager_->getQueue(queueId);
        if (pQueue != nullptr)
        {
            pQueue->push(dataToSend);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

shared_ptr<BasePipelineMessage> PipelineSenderReceiver::receive(EPipelineStageId receivingStageId)
{
    if (stageIdToQueueIdMap_.count(receivingStageId) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(receivingStageId);
        auto pQueue = pQueueManager_->getQueue(queueId);

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
    else
    {
        return nullptr;
    }
}

void PipelineSenderReceiver::receiverThread()
{
    bRunReceiverThread_ = true;
    bReceiverThreadShutdown_ = false;

    while (bRunReceiverThread_)
    {
        auto pReceivedMessage = receive(thisStageId_);

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

    bReceiverThreadShutdown_ = true;
}

void PipelineSenderReceiver::forwardMessage(shared_ptr<BasePipelineMessage> pMessage)
{
    auto destinationId = pMessage->getDestination();
    if (stageIdToQueueIdMap_.count(destinationId) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(destinationId);
        auto pQueue = pQueueManager_->getQueue(queueId);

        if (pQueue != nullptr)
        {
            pQueue->push(pMessage);
        }
    }
}

}  // namespace sc