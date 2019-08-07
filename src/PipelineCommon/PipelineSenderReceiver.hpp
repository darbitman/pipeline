#ifndef PIPELINESENDERRECEIVER_HPP
#define PIPELINESENDERRECEIVER_HPP

#include <cstdint>
#include <memory>

#include "BasePipelineMessage.hpp"
#include "PipelineQueueManager.hpp"

namespace sc
{
class PipelineSenderReceiver
{
  public:
    PipelineSenderReceiver(std::shared_ptr<PipelineQueueManager> pQueueManager);

    bool send(std::shared_ptr<BasePipelineMessage> dataToSend);

    std::shared_ptr<BasePipelineMessage> receive(int32_t currentStageId);

    virtual ~PipelineSenderReceiver();

    // deleted to prevent misuse
    PipelineSenderReceiver(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver(PipelineSenderReceiver&&) = delete;
    PipelineSenderReceiver& operator=(const PipelineSenderReceiver&) = delete;
    PipelineSenderReceiver& operator=(PipelineSenderReceiver&&) = delete;

  private:
    std::shared_ptr<PipelineQueueManager> pQueueManager_;
};
}  // namespace sc

#endif