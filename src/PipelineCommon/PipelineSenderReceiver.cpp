#include "PipelineSenderReceiver.hpp"

#include <memory>
#include <mutex>
#include <thread>

#include "PipelineQueueManager.hpp"

using std::make_unique;
using std::move;
using std::mutex;
using std::thread;
using std::unique_lock;
using std::unique_ptr;

namespace sc
{
PipelineSenderReceiver::PipelineSenderReceiver()
    : bInitialized_(false),
      thisStageId_(EPipelineStageId::MESSAGE_ROUTER),
      bRunReceiverThread_(false),
      bReceiverThreadShutdown_(true)
{
    pQueueManager_ = make_unique<PipelineQueueManager>();
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

void PipelineSenderReceiver::registerNewStage(EPipelineStageId stageId,
                                              EPipelineQueueType queueType)
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(stageId) == 0)
    {
        if (pQueueManager_ != nullptr)
        {
            stageIdToQueueIdMap_[stageId] = pQueueManager_->createNewQueue(queueType);
        }
    }
}

void PipelineSenderReceiver::unregisterStage(EPipelineStageId stageId)
{
    // TODO
}

bool PipelineSenderReceiver::isStageRegistered(EPipelineStageId stageId)
{
    unique_lock<mutex> mapLock(mapMutex_);
    return (stageIdToQueueIdMap_.count(stageId) > 0);
}

bool PipelineSenderReceiver::isInitialized() const { return bInitialized_; }

bool PipelineSenderReceiver::isShutdown() const { return bReceiverThreadShutdown_; }

bool PipelineSenderReceiver::send(unique_ptr<BasePipelineMessage>& dataToSend)
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(thisStageId_) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(thisStageId_);
        mapLock.unlock();

        auto pQueue = pQueueManager_->getQueue(queueId);
        if (pQueue != nullptr)
        {
            pQueue->push(move(dataToSend));
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

unique_ptr<BasePipelineMessage> PipelineSenderReceiver::receive(EPipelineStageId receivingStageId)
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(receivingStageId) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(receivingStageId);
        mapLock.unlock();

        auto pQueue = pQueueManager_->getQueue(queueId);

        if (pQueue != nullptr)
        {
            unique_ptr<BasePipelineMessage> pReceivedMessage = move(pQueue->front());
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

bool PipelineSenderReceiver::canReceive(EPipelineStageId receivingStageId) const
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(receivingStageId) == 0)
    {
        return false;
    }
    auto queueId = stageIdToQueueIdMap_.at(receivingStageId);
    mapLock.unlock();

    auto pQueue = pQueueManager_->getQueue(queueId);
    if (pQueue == nullptr)
    {
        return false;
    }
    else
    {
        return !pQueue->empty();
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

void PipelineSenderReceiver::forwardMessage(unique_ptr<BasePipelineMessage>& pMessage)
{
    auto destinationId = pMessage->getDestination();

    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(destinationId) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(destinationId);
        mapLock.unlock();

        auto pQueue = pQueueManager_->getQueue(queueId);

        if (pQueue != nullptr)
        {
            pQueue->push(move(pMessage));
        }
    }
}

}  // namespace sc
