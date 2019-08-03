#include "PipelineSenderReceiver.hpp"

#include <memory>

using std::shared_ptr;

namespace sc
{
PipelineSenderReceiver::PipelineSenderReceiver(
    shared_ptr<PipelineQueueManager> pQueueManager)
{
}

PipelineSenderReceiver::~PipelineSenderReceiver() {}

bool PipelineSenderReceiver::sendTo(int32_t stageNumberToSendTo,
                                    BasePipelineData* dataToSend)
{
    // TODO IMPLEMENT
}

BasePipelineData* PipelineSenderReceiver::receive(int32_t currentStageNumber)
{
    // TODO IMPLEMENT
}
}  // namespace sc