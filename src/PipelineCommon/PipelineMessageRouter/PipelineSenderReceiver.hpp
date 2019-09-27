#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>

#include "IMessageRouter.hpp"
#include "PipelineCommon.hpp"
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

    virtual void registerComponent(EComponentId componentId,
                                   EComponentLinkType componentLinkType) noexcept override;

    virtual void unregisterComponent(EComponentId componentId) noexcept override;

    virtual bool isComponentRegistered(EComponentId componentId) const noexcept override;

    virtual void sendMessage(std::unique_ptr<BasePipelineMessage>& pMessage) noexcept override;

    virtual void sendMessage(std::unique_ptr<BasePipelineMessage>&& pMessage) noexcept override;

    virtual std::unique_ptr<BasePipelineMessage> receiveMessage(
        EComponentId receivingComponentId) noexcept override;

    virtual bool canReceive(EComponentId receivingComponentId) const noexcept override;

    /// Deleted to prevent misuse
    PipelineSenderReceiver(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver(PipelineSenderReceiver&&) = delete;
    PipelineSenderReceiver& operator=(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver& operator=(PipelineSenderReceiver&&) = delete;

  private:
    bool bInitialized_;

    EComponentId thisComponentId_;

    std::atomic<bool> bRunReceiverThread_;

    std::atomic<bool> bReceiverThreadShutdown_;

    std::unique_ptr<PipelineQueueManager> pQueueManager_;

    std::unordered_map<EComponentId, int32_t> stageIdToQueueIdMap_;

    mutable std::mutex mapMutex_;

    void receiverThread();

    void forwardMessage(std::unique_ptr<BasePipelineMessage>& pMessage);
};

}  // namespace sc
