#include "ShutdownMessage.hpp"

#include "PipelineMessageType.hpp"

namespace sc
{
ShutdownMessage::ShutdownMessage() : messageType_(EPipelineMessageType::MESSAGE_TYPE_SHUTDOWN) {}

ShutdownMessage::~ShutdownMessage() {}

EPipelineMessageType ShutdownMessage::getMessageType() const { return messageType_; }

void* ShutdownMessage::getMessage() const { return nullptr; }

void ShutdownMessage::setMessage(void* pMessage) { return; }

}  // namespace sc
