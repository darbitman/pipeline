#include "ShutdownMessage.hpp"

#include <memory>

#include "PipelineCommon.hpp"

using std::unique_ptr;

namespace sc
{
ShutdownMessage::ShutdownMessage()
    : BasePipelineMessage(EComponentId::UNKNOWN_STAGE, EComponentId::UNKNOWN_STAGE,
                          EMessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

ShutdownMessage::ShutdownMessage(EComponentId source, EComponentId destination,
                                 uint32_t messageNumber)
    : BasePipelineMessage(source, destination, EMessageType::MESSAGE_TYPE_SHUTDOWN,
                          messageNumber)
{
}

ShutdownMessage::~ShutdownMessage() {}

unique_ptr<BasePipelineData>& ShutdownMessage::getOwnedData() { return pNullPipelineData_; }

BasePipelineData* ShutdownMessage::releaseOwnedData() { return nullptr; }

void ShutdownMessage::deleteOwnedData() {}

void ShutdownMessage::setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) {}

}  // namespace sc
