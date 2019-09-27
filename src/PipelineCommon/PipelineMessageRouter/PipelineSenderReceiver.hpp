#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>

#include "IMessageRouter.hpp"
#include "PipelineQueueManager.hpp"

namespace sc
{
class BasePipelineMessage;

class PipelineSenderReceiver : public IMessageRouter
{
  public:
    PipelineSenderReceiver();

    ~PipelineSenderReceiver() = default;

    void initialize();

    bool isInitialized() const noexcept;

    bool isShutdown() const noexcept;

    virtual void registerComponent(uint32_t componentId,
                                   uint32_t componentLinkType) noexcept override;

    virtual void unregisterComponent(uint32_t componentId) noexcept override;

    virtual bool isComponentRegistered(uint32_t componentId) const noexcept override;

    virtual void sendMessage(std::unique_ptr<BasePipelineMessage>& pMessage) noexcept override;

    virtual void sendMessage(std::unique_ptr<BasePipelineMessage>&& pMessage) noexcept override;

    virtual std::unique_ptr<BasePipelineMessage> receiveMessage(
        uint32_t receivingComponentId) noexcept override;

    virtual bool canReceive(uint32_t receivingComponentId) const noexcept override;

    /// Deleted to prevent misuse
    PipelineSenderReceiver(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver(PipelineSenderReceiver&&) = delete;
    PipelineSenderReceiver& operator=(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver& operator=(PipelineSenderReceiver&&) = delete;

  private:
    bool bInitialized_;

    uint32_t thisComponentId_;

    std::atomic<bool> bRunReceiverThread_;

    std::atomic<bool> bReceiverThreadShutdown_;

    std::unique_ptr<PipelineQueueManager> pQueueManager_;

    std::unordered_map<uint32_t, int32_t> stageIdToQueueIdMap_;

    mutable std::mutex mapMutex_;

    void receiverThread();

    void forwardMessage(std::unique_ptr<BasePipelineMessage>& pMessage);
};

}  // namespace sc
