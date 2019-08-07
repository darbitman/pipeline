#ifndef PIPELINESENDERRECEIVER_HPP
#define PIPELINESENDERRECEIVER_HPP

#include <atomic>
#include <cstdint>
#include <memory>

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

    virtual void registerNewStage(int32_t stageId, int32_t queueType);

    virtual void unregisterStage(int32_t stageId);

    virtual bool isInitialized() const;

    virtual bool isShutdown() const;

    virtual bool send(std::shared_ptr<BasePipelineMessage> dataToSend);

    virtual std::shared_ptr<BasePipelineMessage> receive(int32_t receivingStageId);

    // deleted to prevent misuse
    PipelineSenderReceiver(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver(PipelineSenderReceiver&&) = delete;
    PipelineSenderReceiver& operator=(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver& operator=(PipelineSenderReceiver&&) = delete;

  private:
    bool bInitialized_;

    int32_t thisStageId_;

    std::atomic<bool> bRunReceiverThread_;

    std::atomic<bool> bReceiverThreadShutdown_;

    std::shared_ptr<PipelineQueueManager> pQueueManager_;

    std::unordered_map<int32_t, int32_t> stageIdToQueueIdMap_;

    void receiverThread();

    void forwardMessage(std::shared_ptr<BasePipelineMessage> pMessage);
};
}  // namespace sc

#endif