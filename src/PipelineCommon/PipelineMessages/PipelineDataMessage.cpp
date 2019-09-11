#include "PipelineDataMessage.hpp"

#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineCommon.hpp"

using std::move;
using std::unique_ptr;

namespace sc
{
PipelineDataMessage::PipelineDataMessage()
    : BasePipelineMessage(EPipelineStageId::UNKNOWN_STAGE, EPipelineStageId::UNKNOWN_STAGE,
                          EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA, 0)
{
}

PipelineDataMessage::PipelineDataMessage(EPipelineStageId source, EPipelineStageId destination,
                                         uint32_t messageNumber,
                                         unique_ptr<BasePipelineData>& pPipelineData)
    : BasePipelineMessage(source, destination, EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA,
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