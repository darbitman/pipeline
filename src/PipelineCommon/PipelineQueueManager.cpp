#include "PipelineQueueManager.hpp"

#include <cstdint>
#include <memory>
#include <vector>

#include "BasePipelineData.hpp"
#include "PipelineQueueTypes.hpp"
#include "SharedConstSizePQAdapter.hpp"
#include "SharedQueue.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace sc
{
PipelineQueueManager::PipelineQueueManager() : bInitialized_(false) {}

PipelineQueueManager::~PipelineQueueManager() {}

void PipelineQueueManager::initialize(const vector<int32_t>& queueStageNumbers,
                                      const vector<int32_t>& queueTypes)
{
    if (!bInitialized_)
    {
        // make sure for every queue stage there's a type to describe the kind
        // of queue to create
        if (queueStageNumbers.size() != queueTypes.size())
        {
            return;
        }

        // iterator through all the queue stage numbers and create a queue of
        // queueType associate the stage number with the created queue
        size_t numStages = queueStageNumbers.size();
        for (size_t i = 0; i < numStages; ++i)
        {
            // only create a queue if one doesn't exist already for a stage
            if (queueStageNumberToQueueMap_.count(queueStageNumbers[i]) == 0)
            {
                shared_ptr<SharedContainer<BasePipelineData*>> pNewQueue;

                switch (queueTypes[i])
                {
                    case PipelineQueueTypes::QUEUE_TYPE_FIFO:
                    {
                        pNewQueue = dynamic_pointer_cast<SharedContainer<BasePipelineData*>>(
                            make_shared<SharedQueue<VerticalSeamCarverData*>>(true));
                    }
                    break;
                    case PipelineQueueTypes::QUEUE_TYPE_MIN_PQ:
                    {
                        // create a priority queue and use a comparator object that
                        // compares the frame number in VerticalSeamCarverData
                        shared_ptr<ConstSizePriorityQueue<
                            VerticalSeamCarverData*,
                            VerticalSeamCarverData::FrameNumberLessComparator>>
                            pPriorityQueue = make_shared<ConstSizePriorityQueue<
                                VerticalSeamCarverData*,
                                VerticalSeamCarverData::FrameNumberLessComparator>>(1000);

                        // create an adapter to use the same interface as other queues to interface
                        // with the priority queue
                        pNewQueue = dynamic_pointer_cast<SharedContainer<BasePipelineData*>>(
                            make_shared<SharedConstSizePQAdapter<
                                VerticalSeamCarverData*,
                                VerticalSeamCarverData::FrameNumberLessComparator>>(
                                pPriorityQueue));
                    }
                    break;
                    default:
                        // do nothing
                        break;
                }

                if (pNewQueue != nullptr)
                {
                    queueStageNumberToQueueMap_[queueStageNumbers[i]] = pNewQueue;
                }
            }
        }
    }

    bInitialized_ = true;
}

bool PipelineQueueManager::isInitialized() const { return bInitialized_; }

shared_ptr<SharedContainer<BasePipelineData*>> PipelineQueueManager::getQueue(
    int32_t queueStageNumber) const
{
    if (queueStageNumberToQueueMap_.count(queueStageNumber) > 0)
    {
        return queueStageNumberToQueueMap_.at(queueStageNumber);
    }
    else
    {
        return shared_ptr<SharedContainer<BasePipelineData*>>(nullptr);
    }
}

size_t PipelineQueueManager::getNumberOfQueues() const
{
    return queueStageNumberToQueueMap_.size();
}
}  // namespace sc
