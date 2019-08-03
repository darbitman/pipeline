#ifndef PIPELINEQUEUEMANAGER_HPP
#define PIPELINEQUEUEMANAGER_HPP

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "BasePipelineData.hpp"
#include "PipelineQueueTypes.hpp"
#include "SharedContainer.hpp"

namespace sc
{
class PipelineQueueManager
{
  public:
    PipelineQueueManager();

    ~PipelineQueueManager();

    virtual void initialize(const std::vector<int32_t>& queueStageNumbers,
                            const std::vector<int32_t>& queueTypes);

    virtual bool isInitialized() const;

    virtual std::shared_ptr<sc::SharedContainer<BasePipelineData*>> getQueue(
        int32_t queueStageNumber) const;

    virtual size_t getNumberOfQueues() const;

    // deleted to prevent misuse
    PipelineQueueManager(const PipelineQueueManager&) = delete;
    PipelineQueueManager(const PipelineQueueManager&&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&&) = delete;

  private:
    bool bInitialized_;

    std::unordered_map<int32_t,
                       std::shared_ptr<sc::SharedContainer<BasePipelineData*>>>
        queueStageNumberToQueueMap_;
};
}  // namespace sc

#endif
