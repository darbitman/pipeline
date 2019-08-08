#include "PipelineSenderReceiver.hpp"

#include <memory>
#include <mutex>
#include <thread>

#include "PipelineQueueManager.hpp"

using std::make_shared;
using std::mutex;
using std::shared_ptr;
using std::thread;
using std::unique_lock;

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

bool PipelineSenderReceiver::send(shared_ptr<BasePipelineMessage> dataToSend)
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(thisStageId_) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(thisStageId_);
        mapLock.unlock();

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
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(receivingStageId) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(receivingStageId);
        mapLock.unlock();

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

    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(destinationId) != 0)
    {
        auto queueId = stageIdToQueueIdMap_.at(destinationId);
        mapLock.unlock();

        auto pQueue = pQueueManager_->getQueue(queueId);

        if (pQueue != nullptr)
        {
            pQueue->push(pMessage);
        }
    }
}

}  // namespace sc
