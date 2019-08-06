#include "PipelineDataMessage.hpp"

#include "BasePipelineData.hpp"
#include "PipelineMessageType.hpp"

namespace sc
{
PipelineDataMessage::PipelineDataMessage(BasePipelineData* pMessage)
    : messageType_(EPipelineMessageType::MESSAGE_TYPE_PIPELINE_DATA), pMessage_(pMessage)
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
}  // namespace sc