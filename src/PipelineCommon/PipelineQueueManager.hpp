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

    ~PipelineQueueManager() = default;

    /// @brief creates a new queue and returns its queueId which the client should save to be able
    /// to retrieve the actual queue
    /// @param newQueueType
    /// @return int32_t a queueId
    int32_t createNewQueue(EPipelineQueueType newQueueType);

    /// @brief deletes a queue
    /// @param queueId specifies which queue to delete
    /// @return bool indicates whether the queue was deleted or not
    bool deleteQueue(int32_t queueId);

    /// @brief retrieves a queue
    /// @param queueId specifies which queue to retrieve
    /// @return SharedContainer<value_type>* Returns a nullptr if queue doesn't exist
    /// The client should not nor is responsible for deleting the pointer
    SharedContainer<value_type>* getQueue(int32_t queueId) const;

    /// @brief returns the number of queues managed by this PipelineQueueManager
    /// @return size_t
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
