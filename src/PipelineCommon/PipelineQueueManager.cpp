#include "PipelineQueueManager.hpp"

#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "SharedConstSizePQAdapter.hpp"
#include "SharedQueue.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::mutex;
using std::shared_ptr;
using std::static_pointer_cast;
using std::unique_lock;
using std::vector;

namespace sc
{
PipelineQueueManager::PipelineQueueManager() : currentQueueId_(1) {}

PipelineQueueManager::~PipelineQueueManager() {}

int32_t PipelineQueueManager::createNewQueue(EPipelineQueueType newQueueType)
{
    unique_lock<mutex> mapLock(mapMutex_);
    // find an unused queue id
    while (queueIdToQueueMap_.count(currentQueueId_) != 0)
    {
        currentQueueId_++;
    }

    switch (newQueueType)
    {
        case EPipelineQueueType::QUEUE_TYPE_FIFO:
        {
            queueIdToQueueMap_[currentQueueId_] =
                make_shared<SharedQueue<shared_ptr<BasePipelineMessage>>>(true);
        }
        break;
        case EPipelineQueueType::QUEUE_TYPE_MIN_PQ:
        {
            auto pNewPQ = make_shared<ConstSizePriorityQueue<
                shared_ptr<BasePipelineMessage>, PipelineDataMessage::MessageNumberLessComparator>>(
                1000);

            queueIdToQueueMap_[currentQueueId_] = make_shared<SharedConstSizePQAdapter<
                shared_ptr<BasePipelineMessage>, PipelineDataMessage::MessageNumberLessComparator>>(
                pNewPQ, true);
        }
        break;
        default:
            return -1;
            break;
    }

    return currentQueueId_;
}

shared_ptr<SharedContainer<shared_ptr<BasePipelineMessage>>> PipelineQueueManager::getQueue(
    int32_t queueId) const
{
    unique_lock<mutex> mapLock(mapMutex_);
    if (queueIdToQueueMap_.count(queueId) != 0)
    {
        return queueIdToQueueMap_.at(queueId);
    }
    else
    {
        return nullptr;
    }
}

size_t PipelineQueueManager::getNumberOfQueues() const
{
    unique_lock<mutex> mapLock(mapMutex_);
    return queueIdToQueueMap_.size();
}
}  // namespace sc
