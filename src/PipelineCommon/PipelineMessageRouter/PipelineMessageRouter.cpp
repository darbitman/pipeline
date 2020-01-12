#include "PipelineMessageRouter.hpp"

#include <memory>
#include <mutex>
#include <thread>

#include "PipelineMessageBase.hpp"
#include "PipelineQueueManager.hpp"
#include "SharedContainer.hpp"

using std::make_unique;
using std::move;
using std::mutex;
using std::thread;
using std::unique_lock;
using std::unique_ptr;

namespace pipeline
{
PipelineMessageRouter::PipelineMessageRouter()
    : bInitialized_(false),
      thisComponentId_(ComponentId::MESSAGE_ROUTER),
      bRunReceiverThread_(false),
      bReceiverThreadShutdown_(true),
      pQueueManager_(make_unique<PipelineQueueManager>())
{
}

void PipelineMessageRouter::initialize()
{
    if (!bInitialized_)
    {
        bInitialized_ = true;

        registerComponent(thisComponentId_, ComponentLinkType::QUEUE_TYPE_FIFO);

        thread(&PipelineMessageRouter::receiverThread, this).detach();
    }
}

bool PipelineMessageRouter::isInitialized() const noexcept { return bInitialized_; }

bool PipelineMessageRouter::isShutdown() const noexcept { return bReceiverThreadShutdown_; }

void PipelineMessageRouter::registerComponent(uint32_t stageId, uint32_t componentLinkType) noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (stageIdToQueueIdMap_.count(stageId) == 0)
    {
        if (pQueueManager_ != nullptr)
        {
            stageIdToQueueIdMap_[stageId] = pQueueManager_->createNewQueue(componentLinkType);
        }
    }
}

void PipelineMessageRouter::unregisterComponent(uint32_t stageId) noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    try
    {
        auto queueId = stageIdToQueueIdMap_.at(stageId);

        try
        {
            pQueueManager_->deleteQueue(queueId);
        }
        catch (const std::invalid_argument& e)
        {
            // queueId doesn't exist
        }
    }
    catch (const std::out_of_range& e)
    {
        // stageId has no queueId associated with it
    }
}

bool PipelineMessageRouter::isComponentRegistered(uint32_t stageId) const noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    try
    {
        stageIdToQueueIdMap_.at(stageId);
        return true;
    }
    catch (const std::out_of_range& e)
    {
        return false;
    }
}

void PipelineMessageRouter::sendMessage(unique_ptr<PipelineMessageBase>& pMessage) noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    try
    {
        auto queueId = stageIdToQueueIdMap_.at(thisComponentId_);
        mapLock.unlock();

        if (auto pQueue = pQueueManager_->getQueue(queueId); pQueue != nullptr)
        {
            pQueue->push(move(pMessage));
        }
    }
    catch (const std::out_of_range& e)
    {
        // drop the message
    }
}

void PipelineMessageRouter::sendMessage(unique_ptr<PipelineMessageBase>&& pMessage) noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    try
    {
        auto queueId = stageIdToQueueIdMap_.at(thisComponentId_);
        mapLock.unlock();

        if (auto pQueue = pQueueManager_->getQueue(queueId); pQueue != nullptr)
        {
            pQueue->push(move(pMessage));
        }
    }
    catch (const std::out_of_range& e)
    {
        // drop the message
    }
}

unique_ptr<PipelineMessageBase> PipelineMessageRouter::receiveMessage(
    uint32_t receivingComponentId) noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    try
    {
        auto queueId = stageIdToQueueIdMap_.at(receivingComponentId);
        mapLock.unlock();

        if (auto pQueue = pQueueManager_->getQueue(queueId); pQueue != nullptr)
        {
            unique_ptr<PipelineMessageBase> pReceivedMessage = move(pQueue->front());
            pQueue->pop();
            return pReceivedMessage;
        }
        else
        {
            return unique_ptr<PipelineMessageBase>();
        }
    }
    catch (const std::out_of_range& e)
    {
        return unique_ptr<PipelineMessageBase>();
    }
}

bool PipelineMessageRouter::canReceive(uint32_t receivingStageId) const noexcept
{
    unique_lock<mutex> mapLock(mapMutex_);
    try
    {
        auto queueId = stageIdToQueueIdMap_.at(receivingStageId);
        mapLock.unlock();

        if (auto pQueue = pQueueManager_->getQueue(queueId); pQueue != nullptr)
        {
            return !pQueue->empty();
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception& e)
    {
        return false;
    }
}

void PipelineMessageRouter::receiverThread()
{
    bRunReceiverThread_ = true;
    bReceiverThreadShutdown_ = false;

    while (bRunReceiverThread_)
    {
        auto pReceivedMessage = receiveMessage(thisComponentId_);

        if (pReceivedMessage != nullptr)
        {
            auto receivedMessageType = pReceivedMessage->getMessageType();

            auto messageDestination = pReceivedMessage->getDestination();

            if (messageDestination != thisComponentId_)
            {
                forwardMessage(pReceivedMessage);
            }
            else
            {
                if (receivedMessageType == MessageType::MESSAGE_TYPE_PIPELINE_DATA)
                {
                    // TODO process data
                }
                else if (receivedMessageType == MessageType::MESSAGE_TYPE_SHUTDOWN)
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

void PipelineMessageRouter::forwardMessage(unique_ptr<PipelineMessageBase>& pMessage)
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

}  // namespace pipeline
