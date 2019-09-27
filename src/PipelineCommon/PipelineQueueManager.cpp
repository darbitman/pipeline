#include "PipelineQueueManager.hpp"

#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "PriorityQueue.hpp"
#include "SharedPriorityQueueAdapter.hpp"
#include "SharedQueue.hpp"

using std::make_unique;
using std::mutex;
using std::unique_lock;
using std::unique_ptr;
using std::vector;

namespace sc
{
PipelineQueueManager::PipelineQueueManager() : currentQueueId_(1) {}

int32_t PipelineQueueManager::createNewQueue(EComponentLinkType newQueueType)
{
    unique_lock<mutex> mapLock(mapMutex_);
    // find an unused queue id
    while (queueIdToQueueMap_.count(currentQueueId_) != 0)
    {
        currentQueueId_++;
    }

    switch (newQueueType)
    {
        case EComponentLinkType::QUEUE_TYPE_FIFO:
        {
            queueIdToQueueMap_[currentQueueId_] = make_unique<SharedQueue<value_type>>(true);
        }
        break;
        case EComponentLinkType::QUEUE_TYPE_MIN_PQ:
        {
            using comparator_type = PipelineDataMessage::MessageNumberLessComparator;

            auto pNewPQ = make_unique<PriorityQueue<value_type, comparator_type>>(1000);

            queueIdToQueueMap_[currentQueueId_] =
                make_unique<SharedPriorityQueueAdapter<value_type, comparator_type>>(pNewPQ, true);
        }
        break;
        default:
            throw std::invalid_argument(
                "PipelineQueueManager::createNewQueue(): Invalid EComponentLinkType");
            break;
    }

    return currentQueueId_;
}

void PipelineQueueManager::deleteQueue(int32_t queueId)
{
    if (queueIdToQueueMap_.erase(queueId) == 0)
    {
        throw std::invalid_argument("PipelineQueueManager::deleteQueue(): Queue ID doesn't exist");
    }
}

SharedContainer<PipelineQueueManager::value_type>* PipelineQueueManager::getQueue(
    int32_t queueId) const
{
    unique_lock<mutex> mapLock(mapMutex_);

    try
    {
        return queueIdToQueueMap_.at(queueId).get();
    }
    catch (std::out_of_range& e)
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
