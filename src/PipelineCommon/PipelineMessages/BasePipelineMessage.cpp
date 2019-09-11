#include "BasePipelineMessage.hpp"

namespace sc
{

BasePipelineMessage::BasePipelineMessage(EPipelineStageId source, EPipelineStageId destination,
                                         EPipelineMessageType messageType, uint32_t messageNumber)
    : source_(source),
      destination_(destination),
      messageType_(messageType),
      messageNumber_(messageNumber)
{
}

BasePipelineMessage::~BasePipelineMessage() {}

}  // namespace sc
