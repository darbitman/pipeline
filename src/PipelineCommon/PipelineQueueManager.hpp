#ifndef PIPELINEQUEUEMANAGER_HPP
#define PIPELINEQUEUEMANAGER_HPP

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "SharedContainer.hpp"

namespace sc
{
class PipelineQueueManager
{
  public:
    PipelineQueueManager();

    ~PipelineQueueManager();

    virtual int32_t createNewQueue(EPipelineQueueType newQueueType);

    virtual std::shared_ptr<SharedContainer<std::shared_ptr<BasePipelineMessage>>> getQueue(
        int32_t queueId) const;

    virtual size_t getNumberOfQueues() const;

    // deleted to prevent misuse
    PipelineQueueManager(const PipelineQueueManager&) = delete;
    PipelineQueueManager(const PipelineQueueManager&&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&&) = delete;

  private:
    int32_t currentQueueId_;

    std::unordered_map<int32_t,
                       std::shared_ptr<sc::SharedContainer<std::shared_ptr<BasePipelineMessage>>>>
        queueIdToQueueMap_;
};
}  // namespace sc

#endif
