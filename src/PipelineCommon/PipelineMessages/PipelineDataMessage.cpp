#include "PipelineDataMessage.hpp"

#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineCommon.hpp"

using std::shared_ptr;

namespace sc
{
PipelineDataMessage::PipelineDataMessage(EPipelineStageId source, EPipelineStageId destination,
                                         shared_ptr<BasePipelineData> pPipelineData)
    : messageType_(EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA),
      source_(source),
      destination_(destination),
      messageNumber_(0),
      pPipelineData_(pPipelineData)
{
}

PipelineDataMessage::~PipelineDataMessage() {}

EPipelineMessageType PipelineDataMessage::getMessageType() const { return messageType_; }

shared_ptr<BasePipelineData> PipelineDataMessage::getPipelineData() const { return pPipelineData_; }

void PipelineDataMessage::setPipelineData(shared_ptr<BasePipelineData> pPipelineData)
{
    pPipelineData_ = pPipelineData;
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