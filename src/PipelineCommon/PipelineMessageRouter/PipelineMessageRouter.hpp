#ifndef PIPELINEMESSAGEROUTER_HPP
#define PIPELINEMESSAGEROUTER_HPP

#include <atomic>
#include <memory>

#include "PipelineSenderReceiver.hpp"
#include "StageNumbers.hpp"

namespace sc
{
class PipelineMessageRouter
{
  public:
    PipelineMessageRouter(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver,
                          int32_t thisStage);

    virtual ~PipelineMessageRouter();

    virtual void initialize();

    // deleted to prevent misuse
    PipelineMessageRouter(const PipelineMessageRouter&) = delete;
    PipelineMessageRouter(const PipelineMessageRouter&&) = delete;
    PipelineMessageRouter& operator=(const PipelineMessageRouter&) = delete;
    PipelineMessageRouter& operator=(const PipelineMessageRouter&&) = delete;

  private:
    bool bInitialized_;

    int32_t thisStage_;

    std::atomic<bool> bRunReceiverThread_;

    std::atomic<bool> bReceiverThreadShutdown_;

    std::shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    void receiverThread();
}
}  // namespace sc

#endif
