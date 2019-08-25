#include "ShutdownMessage.hpp"

#include <memory>

#include "PipelineCommon.hpp"

using std::unique_ptr;

namespace sc
{
ShutdownMessage::ShutdownMessage(EPipelineStageId destination)
    : messageType_(EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN),
      destination_(destination),
      messageNumber_(0)
{
}

ShutdownMessage::~ShutdownMessage() {}

unique_ptr<BasePipelineData>& ShutdownMessage::getData() { return pPipelineData_; }

EPipelineMessageType ShutdownMessage::getMessageType() const { return messageType_; }

BasePipelineData* ShutdownMessage::releasePipelineData() { return nullptr; }

void ShutdownMessage::resetPipelineData() {}

void ShutdownMessage::setPipelineData(std::unique_ptr<BasePipelineData>& pPipelineData) {}

void ShutdownMessage::setSource(EPipelineStageId source) { source_ = source; }

EPipelineStageId ShutdownMessage::getSource() const { return source_; }

void ShutdownMessage::setDestination(EPipelineStageId destination) { destination_ = destination; }

EPipelineStageId ShutdownMessage::getDestination() const { return destination_; }

void ShutdownMessage::setMessageNumber(int32_t newMessageNumber)
{
    messageNumber_ = newMessageNumber;
}

int32_t ShutdownMessage::getMessageNumber() const { return messageNumber_; }

}  // namespace sc
