#include "ShutdownMessage.hpp"

#include "PipelineCommon.hpp"

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

void* ShutdownMessage::getMessage() const { return nullptr; }

void ShutdownMessage::setMessage(void* pMessage) { return; }

void ShutdownMessage::setDestination(EPipelineStageId destination) { destination_ = destination; }

EPipelineStageId ShutdownMessage::getDestination() const { return destination_; }

void ShutdownMessage::setMessageNumber(int32_t newMessageNumber)
{
    messageNumber_ = newMessageNumber;
}

int32_t ShutdownMessage::getMessageNumber() const { return messageNumber_; }

}  // namespace sc
