#include "PipelineDataMessage.hpp"

#include "BasePipelineData.hpp"
#include "PipelineMessageType.hpp"

namespace sc
{
PipelineDataMessage::PipelineDataMessage(int32_t destination, BasePipelineData* pMessage)
    : messageType_(EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA),
      destination_(destination),
      messageNumber_(0),
      pMessage_(pMessage)
{
}

PipelineDataMessage::~PipelineDataMessage()
{
    if (pMessage_ != nullptr)
    {
        delete ((BasePipelineData*)pMessage_);
        pMessage_ = nullptr;
    }
}

EPipelineMessageType PipelineDataMessage::getMessageType() const { return messageType_; }

void* PipelineDataMessage::getMessage() const { return pMessage_; }

void PipelineDataMessage::setMessage(void* pMessage) { pMessage_ = pMessage; }

void PipelineDataMessage::setDestination(int32_t destination) { destination_ = destination; }

int32_t PipelineDataMessage::getDestination() const { return destination_; }

void PipelineDataMessage::setMessageNumber(int32_t newMessageNumber)
{
    messageNumber_ = newMessageNumber;
}

int32_t PipelineDataMessage::getMessageNumber() const { return messageNumber_; }
}  // namespace sc