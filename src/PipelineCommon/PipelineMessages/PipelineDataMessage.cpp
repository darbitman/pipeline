#include "PipelineDataMessage.hpp"

#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineCommon.hpp"

using std::move;
using std::unique_ptr;

namespace sc
{
PipelineDataMessage::PipelineDataMessage(EPipelineStageId source, EPipelineStageId destination,
                                         unique_ptr<BasePipelineData>& pPipelineData)
    : messageType_(EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA),
      source_(source),
      destination_(destination),
      messageNumber_(0),
      pPipelineData_(move(pPipelineData))
{
}

PipelineDataMessage::~PipelineDataMessage() {}

unique_ptr<BasePipelineData>& PipelineDataMessage::getData() { return pPipelineData_; }

EPipelineMessageType PipelineDataMessage::getMessageType() const { return messageType_; }

BasePipelineData* PipelineDataMessage::releasePipelineData() { return pPipelineData_.release(); }

void PipelineDataMessage::resetPipelineData() { pPipelineData_.reset(nullptr); }

void PipelineDataMessage::setPipelineData(std::unique_ptr<BasePipelineData>& pPipelineData)
{
    pPipelineData_.reset(nullptr);
    pPipelineData_.swap(pPipelineData);
}

void PipelineDataMessage::setSource(EPipelineStageId source) { source_ = source; }

EPipelineStageId PipelineDataMessage::getSource() const { return source_; }

void PipelineDataMessage::setDestination(EPipelineStageId destination)
{
    destination_ = destination;
}

EPipelineStageId PipelineDataMessage::getDestination() const { return destination_; }

void PipelineDataMessage::setMessageNumber(int32_t newMessageNumber)
{
    messageNumber_ = newMessageNumber;
}

int32_t PipelineDataMessage::getMessageNumber() const { return messageNumber_; }

}  // namespace sc