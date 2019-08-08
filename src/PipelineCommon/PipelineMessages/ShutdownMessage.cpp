#include "ShutdownMessage.hpp"

#include <memory>

#include "PipelineCommon.hpp"

using std::shared_ptr;

namespace sc
{
ShutdownMessage::ShutdownMessage(EPipelineStageId destination)
    : messageType_(EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN),
      destination_(destination),
      messageNumber_(0)
{
}

ShutdownMessage::~ShutdownMessage() {}

EPipelineMessageType ShutdownMessage::getMessageType() const { return messageType_; }

shared_ptr<BasePipelineData> ShutdownMessage::getPipelineData() const { return nullptr; }

void ShutdownMessage::setPipelineData(shared_ptr<BasePipelineData> pPipelineData) { return; }

void ShutdownMessage::setDestination(EPipelineStageId destination) { destination_ = destination; }

EPipelineStageId ShutdownMessage::getDestination() const { return destination_; }

void ShutdownMessage::setMessageNumber(int32_t newMessageNumber)
{
    messageNumber_ = newMessageNumber;
}

int32_t ShutdownMessage::getMessageNumber() const { return messageNumber_; }

}  // namespace sc
