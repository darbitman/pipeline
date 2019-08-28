#ifndef PIPELINESENDERRECEIVER_HPP
#define PIPELINESENDERRECEIVER_HPP

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>

#include "BasePipelineMessage.hpp"
#include "PipelineCommon.hpp"
#include "PipelineQueueManager.hpp"

namespace sc
{
class PipelineSenderReceiver
{
  public:
    PipelineSenderReceiver();

    ~PipelineSenderReceiver() = default;

    void initialize();

    void registerNewStage(EPipelineStageId stageId, EPipelineQueueType queueType);

    void unregisterStage(EPipelineStageId stageId);

    bool isStageRegistered(EPipelineStageId stageId);

    bool isInitialized() const;

    bool isShutdown() const;

    bool send(std::unique_ptr<BasePipelineMessage>& dataToSend);

    std::unique_ptr<BasePipelineMessage> receive(EPipelineStageId receivingStageId);

    bool canReceive(EPipelineStageId receivingStageId) const;

    // deleted to prevent misuse
    PipelineSenderReceiver(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver(PipelineSenderReceiver&&) = delete;
    PipelineSenderReceiver& operator=(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver& operator=(PipelineSenderReceiver&&) = delete;

  private:
    bool bInitialized_;

    EPipelineStageId thisStageId_;

    std::atomic<bool> bRunReceiverThread_;

    std::atomic<bool> bReceiverThreadShutdown_;

    std::unique_ptr<PipelineQueueManager> pQueueManager_;

    std::unordered_map<EPipelineStageId, int32_t> stageIdToQueueIdMap_;

    mutable std::mutex mapMutex_;

    void receiverThread();

    void forwardMessage(std::unique_ptr<BasePipelineMessage>& pMessage);
};

}  // namespace sc

#endif
