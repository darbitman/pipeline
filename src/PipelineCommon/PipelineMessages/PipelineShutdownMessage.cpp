#include "PipelineShutdownMessage.hpp"

#include <memory>

#include "PipelineIdentifiers.hpp"

using std::unique_ptr;

namespace pipeline
{
PipelineShutdownMessage::PipelineShutdownMessage()
    : PipelineMessageBase(ComponentId::UNKNOWN_COMPONENT, ComponentId::UNKNOWN_COMPONENT,
                          MessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

PipelineShutdownMessage::PipelineShutdownMessage(uint32_t source, uint32_t destination, uint32_t messageNumber)
    : PipelineMessageBase(source, destination, MessageType::MESSAGE_TYPE_SHUTDOWN, messageNumber)
{
}

void PipelineShutdownMessage::setOwnedData([
    [maybe_unused]] std::unique_ptr<BasePipelineData>& pPipelineData) noexcept
{
}

unique_ptr<BasePipelineData>& PipelineShutdownMessage::getOwnedData() noexcept
{
    return pNullPipelineData_;
}

BasePipelineData* PipelineShutdownMessage::releaseOwnedData() noexcept { return nullptr; }

void PipelineShutdownMessage::deleteOwnedData() noexcept {}

}  // namespace pipeline
