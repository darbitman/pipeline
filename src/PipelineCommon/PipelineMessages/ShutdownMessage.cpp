#include "ShutdownMessage.hpp"

#include <memory>

#include "PipelineCommon.hpp"

using std::unique_ptr;

namespace sc
{
ShutdownMessage::ShutdownMessage()
    : BasePipelineMessage(EPipelineStageId::UNKNOWN_STAGE, EPipelineStageId::UNKNOWN_STAGE,
                          EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

ShutdownMessage::ShutdownMessage(EPipelineStageId source, EPipelineStageId destination,
                                 uint32_t messageNumber)
    : BasePipelineMessage(source, destination, EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN,
                          messageNumber)
{
}

ShutdownMessage::~ShutdownMessage() {}

unique_ptr<BasePipelineData>& ShutdownMessage::getOwnedData() { return pNullPipelineData_; }

BasePipelineData* ShutdownMessage::releaseOwnedData() { return nullptr; }

void ShutdownMessage::deleteOwnedData() {}

void ShutdownMessage::setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) {}

}  // namespace sc
