#include "PipelineQueueManager.hpp"

#include <cstdint>
#include <memory>
#include <vector>

#include "PipelineDataMessage.hpp"
#include "PipelineQueueTypes.hpp"
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
                shared_ptr<SharedContainer<shared_ptr<PipelineDataMessage>>> pNewSharedContainer;

                switch (queueTypes[i])
                {
                    case PipelineQueueTypes::QUEUE_TYPE_FIFO:
                    {
                        pNewSharedContainer =
                            make_shared<SharedQueue<shared_ptr<PipelineDataMessage>>>(true);
                    }
                    break;
                    case PipelineQueueTypes::QUEUE_TYPE_MIN_PQ:
                    {
                        // TODO implement
                    }
                    break;
                    default:
                        // do nothing
                        break;
                }

                if (pNewSharedContainer != nullptr)
                {
                    queueStageNumberToQueueMap_[queueStageNumbers[i]] = pNewSharedContainer;
                }
            }
        }
    }

    bInitialized_ = true;
}

bool PipelineQueueManager::isInitialized() const { return bInitialized_; }

shared_ptr<SharedContainer<shared_ptr<PipelineDataMessage>>> PipelineQueueManager::getQueue(
    int32_t queueStageNumber) const
{
    shared_ptr<SharedContainer<shared_ptr<PipelineDataMessage>>> pQueue(nullptr);

    if (queueStageNumberToQueueMap_.count(queueStageNumber) > 0)
    {
        pQueue = queueStageNumberToQueueMap_.at(queueStageNumber);
    }

    return pQueue;
}

size_t PipelineQueueManager::getNumberOfQueues() const
{
    return queueStageNumberToQueueMap_.size();
}
}  // namespace sc
