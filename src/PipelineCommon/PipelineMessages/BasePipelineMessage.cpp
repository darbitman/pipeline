#include "BasePipelineMessage.hpp"

namespace sc
{

BasePipelineMessage::BasePipelineMessage(EComponentId source, EComponentId destination,
                                         EMessageType messageType, uint32_t messageNumber)
    : source_(source),
      destination_(destination),
      messageType_(messageType),
      messageNumber_(messageNumber)
{
}

BasePipelineMessage::~BasePipelineMessage() {}

}  // namespace sc
