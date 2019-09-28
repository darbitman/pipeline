#include "PipelineMessageBase.hpp"

namespace pipeline
{
PipelineMessageBase::PipelineMessageBase(uint32_t source, uint32_t destination,
                                         uint32_t messageType, uint32_t messageNumber)
    : source_(source),
      destination_(destination),
      messageType_(messageType),
      messageNumber_(messageNumber)
{
}

}  // namespace pipeline
