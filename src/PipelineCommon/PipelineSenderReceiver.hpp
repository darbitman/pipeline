#ifndef PIPELINESENDERRECEIVER_HPP
#define PIPELINESENDERRECEIVER_HPP

#include <atomic>
#include <cstdint>
#include <memory>

#include "PipelineCommon.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineQueueManager.hpp"

namespace sc
{
class PipelineSenderReceiver
{
  public:
    PipelineSenderReceiver();

    virtual ~PipelineSenderReceiver();

    virtual void initialize();

    virtual void registerNewStage(EPipelineStageId stageId, EPipelineQueueType queueType);

    virtual void unregisterStage(EPipelineStageId stageId);

    virtual bool isStageRegistered(EPipelineStageId stageId);

    virtual bool isInitialized() const;

    virtual bool isShutdown() const;

    virtual bool send(std::shared_ptr<BasePipelineMessage> dataToSend);

    virtual std::shared_ptr<BasePipelineMessage> receive(EPipelineStageId receivingStageId);

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

    std::shared_ptr<PipelineQueueManager> pQueueManager_;

    std::unordered_map<EPipelineStageId, int32_t> stageIdToQueueIdMap_;

    void receiverThread();

    void forwardMessage(std::shared_ptr<BasePipelineMessage> pMessage);
};
}  // namespace sc

#endif