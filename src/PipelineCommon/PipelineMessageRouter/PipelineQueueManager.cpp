#include "PipelineQueueManager.hpp"

#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include "PipelineDataMessage.hpp"
#include "PipelineIdentifiers.hpp"
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
PipelineQueueManager::PipelineQueueManager() : currentQueueId_(STARTING_QUEUE_ID) {}

int32_t PipelineQueueManager::createNewQueue(uint32_t componentLinkType)
{
    unique_lock<mutex> mapLock(mapMutex_);
    // find an unused queue id
    while (queueIdToQueueMap_.count(currentQueueId_) != 0)
    {
        currentQueueId_++;
    }

    switch (componentLinkType)
    {
        case ComponentLinkType::QUEUE_TYPE_FIFO:
        {
            // create a thread safe blocking FIFO queue
            queueIdToQueueMap_[currentQueueId_] = make_unique<SharedQueue<stored_data_type>>(true);
        }
        break;

        case ComponentLinkType::QUEUE_TYPE_MIN_PQ:
        {
            using comparator_type = PipelineDataMessage::MessageNumberLessComparator;

            // create a min-oriented priority queue which uses the message number as its 'priority'
            auto pNewPQ = make_unique<PriorityQueue<stored_data_type, comparator_type>>(1000);

            // create an adapter ("wrapper" around the PQ just created). This also blocks and is
            // thread safe
            queueIdToQueueMap_[currentQueueId_] =
                make_unique<SharedPriorityQueueAdapter<stored_data_type, comparator_type>>(pNewPQ,
                                                                                           true);
        }
        break;

        default:
            throw std::invalid_argument(
                "PipelineQueueManager::createNewQueue(): Invalid ComponentLinkType");
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

SharedContainer<PipelineQueueManager::stored_data_type>* PipelineQueueManager::getQueue(
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
