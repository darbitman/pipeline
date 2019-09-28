#include "PipelineDataMessage.hpp"

#include <cstdint>
#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineIdentifiers.hpp"

using std::move;
using std::unique_ptr;

namespace pipeline
{
PipelineDataMessage::PipelineDataMessage()
    : PipelineMessageBase(ComponentId::UNKNOWN_COMPONENT, ComponentId::UNKNOWN_COMPONENT,
                          MessageType::MESSAGE_TYPE_PIPELINE_DATA, STARTING_MESSAGE_NUMBER)
{
}

PipelineDataMessage::PipelineDataMessage(uint32_t source, uint32_t destination,
                                         uint32_t messageNumber,
                                         unique_ptr<BasePipelineData>& pPipelineData)
    : PipelineMessageBase(source, destination, MessageType::MESSAGE_TYPE_PIPELINE_DATA,
                          messageNumber),
      pPipelineData_(move(pPipelineData))
{
}

void PipelineDataMessage::setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) noexcept
{
    pPipelineData_.reset(nullptr);
    pPipelineData_.swap(pPipelineData);
}

unique_ptr<BasePipelineData>& PipelineDataMessage::getOwnedData() noexcept
{
    return pPipelineData_;
}

BasePipelineData* PipelineDataMessage::releaseOwnedData() noexcept
{
    return pPipelineData_.release();
}

void PipelineDataMessage::deleteOwnedData() noexcept { pPipelineData_.reset(nullptr); }

}  // namespace pipeline