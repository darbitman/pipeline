#pragma once

#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "PipelineIdentifiers.hpp"

namespace sc
{
template <typename T>
class SharedContainer;

class BasePipelineMessage;

class PipelineQueueManager
{
  private:
    using stored_data_type = std::unique_ptr<BasePipelineMessage>;

  public:
    PipelineQueueManager();

    ~PipelineQueueManager() = default;

    /// @brief creates a new queue and returns its queueId which the client can use to later
    /// retrieve the queue
    /// @param componentLinkType
    /// @return int32_t A unique identifier for the queue created
    /// @throw std::invalid_argument If componentLinkType doesn't exist
    int32_t createNewQueue(uint32_t componentLinkType);

    /// @brief deletes a queue
    /// @param queueId specifies which queue to delete
    /// @return bool indicates whether the queue was deleted or not
    /// @throw std::invalid_argument If queueId doesn't exist
    void deleteQueue(int32_t queueId);

    /// @brief retrieves a queue
    /// @param queueId specifies which queue to retrieve
    /// @return SharedContainer<stored_data_type>* Returns a nullptr if queue doesn't exist
    /// The client should not nor is responsible for deleting the pointer
    SharedContainer<stored_data_type>* getQueue(int32_t queueId) const;

    /// @brief returns the number of queues managed by this PipelineQueueManager
    /// @return size_t
    size_t getNumberOfQueues() const;

    /// Deleted to prevent misuse
    PipelineQueueManager(const PipelineQueueManager&) = delete;
    PipelineQueueManager(const PipelineQueueManager&&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&) = delete;
    PipelineQueueManager& operator=(const PipelineQueueManager&&) = delete;

  private:
    static constexpr uint32_t STARTING_QUEUE_ID{1};

    int32_t currentQueueId_;

    std::unordered_map<int32_t, std::unique_ptr<SharedContainer<stored_data_type>>>
        queueIdToQueueMap_;

    mutable std::mutex mapMutex_;
};
}  // namespace sc
