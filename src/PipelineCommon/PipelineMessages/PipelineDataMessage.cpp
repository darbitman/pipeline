#include "PipelineDataMessage.hpp"

#include <cstdint>
#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineIdentifiers.hpp"

using std::move;
using std::unique_ptr;

namespace sc
{
PipelineDataMessage::PipelineDataMessage()
    : BasePipelineMessage(ComponentId::UNKNOWN_COMPONENT, ComponentId::UNKNOWN_COMPONENT,
                          MessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

PipelineDataMessage::PipelineDataMessage(uint32_t source, uint32_t destination,
                                         uint32_t messageNumber,
                                         unique_ptr<BasePipelineData>& pPipelineData)
    : BasePipelineMessage(source, destination, MessageType::MESSAGE_TYPE_PIPELINE_DATA,
                          messageNumber),
      pPipelineData_(move(pPipelineData))
{
}

void PipelineDataMessage::setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData)
{
    pPipelineData_.reset(nullptr);
    pPipelineData_.swap(pPipelineData);
}

unique_ptr<BasePipelineData>& PipelineDataMessage::getOwnedData() { return pPipelineData_; }

BasePipelineData* PipelineDataMessage::releaseOwnedData() { return pPipelineData_.release(); }

void PipelineDataMessage::deleteOwnedData() { pPipelineData_.reset(nullptr); }

}  // namespace sc