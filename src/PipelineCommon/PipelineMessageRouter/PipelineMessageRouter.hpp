#ifndef PIPELINEMESSAGEROUTER_HPP
#define PIPELINEMESSAGEROUTER_HPP

#include <atomic>
#include <memory>
#include <unordered_map>

#include "PipelineSenderReceiver.hpp"
#include "StageNumbers.hpp"

namespace sc
{
class PipelineMessageRouter
{
  public:
    PipelineMessageRouter(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver,
                          std::shared_ptr<PipelineQueueManager> pQueueManager);

    virtual ~PipelineMessageRouter();

    virtual void initialize();

    virtual bool isInitialized() const;

    void registerNewStage(int32_t stageId, int32_t queueType);

    // deleted to prevent misuse
    PipelineMessageRouter(const PipelineMessageRouter&) = delete;
    PipelineMessageRouter(const PipelineMessageRouter&&) = delete;
    PipelineMessageRouter& operator=(const PipelineMessageRouter&) = delete;
    PipelineMessageRouter& operator=(const PipelineMessageRouter&&) = delete;

  private:
    bool bInitialized_;

    int32_t thisStageId_;

    std::atomic<bool> bRunReceiverThread_;

    std::atomic<bool> bReceiverThreadShutdown_;

    std::shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    std::shared_ptr<PipelineQueueManager> pQueueManager_;

    std::unordered_map<int32_t, int32_t> stageIdToQueueIdMap_;

    void receiverThread();

    void forwardMessage(std::shared_ptr<BasePipelineMessage> pMessage);
};
}  // namespace sc

#endif
