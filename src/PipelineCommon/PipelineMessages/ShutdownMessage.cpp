#include "ShutdownMessage.hpp"

#include <memory>

#include "PipelineIdentifiers.hpp"

using std::unique_ptr;

namespace sc
{
ShutdownMessage::ShutdownMessage()
    : BasePipelineMessage(ComponentId::UNKNOWN_COMPONENT, ComponentId::UNKNOWN_COMPONENT,
                          MessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

ShutdownMessage::ShutdownMessage(uint32_t source, uint32_t destination,
                                 uint32_t messageNumber)
    : BasePipelineMessage(source, destination, MessageType::MESSAGE_TYPE_SHUTDOWN,
                          messageNumber)
{
}

ShutdownMessage::~ShutdownMessage() {}

unique_ptr<BasePipelineData>& ShutdownMessage::getOwnedData() { return pNullPipelineData_; }

BasePipelineData* ShutdownMessage::releaseOwnedData() { return nullptr; }

void ShutdownMessage::deleteOwnedData() {}

void ShutdownMessage::setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) {}

}  // namespace sc
