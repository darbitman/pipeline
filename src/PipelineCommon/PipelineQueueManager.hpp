#ifndef PIPELINEQUEUEMANAGER_HPP
#define PIPELINEQUEUEMANAGER_HPP

#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "SharedContainer.hpp"

namespace sc
{
class PipelineQueueManager
{
  private:
    using value_type = std::unique_ptr<BasePipelineMessage>;

  public:
    PipelineQueueManager();

    ~PipelineQueueManager();

    int32_t createNewQueue(EPipelineQueueType newQueueType);

    SharedContainer<value_type>* getQueue(int32_t queueId) const;

    size_t getNumberOfQueues() const;

    // deleted to prevent misuse
    PipelineQueueManager(const PipelineQueueManager&) = delete;
    PipelineQueueManager(const PipelineQueueManager&&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&&) = delete;

  private:
    int32_t currentQueueId_;

    std::unordered_map<int32_t, std::unique_ptr<sc::SharedContainer<value_type>>>
        queueIdToQueueMap_;

    mutable std::mutex mapMutex_;
};
}  // namespace sc

#endif
