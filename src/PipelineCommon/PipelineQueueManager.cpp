#include "PipelineQueueManager.hpp"

#include <cstdint>
#include <memory>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "SharedConstSizePQAdapter.hpp"
#include "SharedQueue.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;
using std::static_pointer_cast;
using std::vector;

namespace sc
{
PipelineQueueManager::PipelineQueueManager() : currentQueueId_(1) {}

PipelineQueueManager::~PipelineQueueManager() {}

int32_t PipelineQueueManager::createNewQueue(EPipelineQueueType newQueueType)
{
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
    if (queueIdToQueueMap_.count(queueId) != 0)
    {
        return queueIdToQueueMap_.at(queueId);
    }
    else
    {
        return nullptr;
    }
}

size_t PipelineQueueManager::getNumberOfQueues() const { return queueIdToQueueMap_.size(); }
}  // namespace sc
