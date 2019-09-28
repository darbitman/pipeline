#include "ShutdownMessage.hpp"

#include <memory>

#include "PipelineIdentifiers.hpp"

using std::unique_ptr;

namespace pipeline
{
ShutdownMessage::ShutdownMessage()
    : BasePipelineMessage(ComponentId::UNKNOWN_COMPONENT, ComponentId::UNKNOWN_COMPONENT,
                          MessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

ShutdownMessage::ShutdownMessage(uint32_t source, uint32_t destination, uint32_t messageNumber)
    : BasePipelineMessage(source, destination, MessageType::MESSAGE_TYPE_SHUTDOWN, messageNumber)
{
}

void ShutdownMessage::setOwnedData([
    [maybe_unused]] std::unique_ptr<BasePipelineData>& pPipelineData) noexcept
{
}

unique_ptr<BasePipelineData>& ShutdownMessage::getOwnedData() noexcept
{
    return pNullPipelineData_;
}

BasePipelineData* ShutdownMessage::releaseOwnedData() noexcept { return nullptr; }

void ShutdownMessage::deleteOwnedData() noexcept {}

}  // namespace pipeline
