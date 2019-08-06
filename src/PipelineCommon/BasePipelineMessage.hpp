#ifndef BASEPIPELINEMESSAGE_HPP
#define BASEPIPELINEMESSAGE_HPP

#include <cstdint>

#include "PipelineMessageType.hpp"
#include "StageNumbers.hpp"

namespace sc
{
class BasePipelineMessage
{
  public:
    virtual ~BasePipelineMessage() = 0;

    virtual EPipelineMessageType getMessageType() const = 0;

    virtual void* getMessage() const = 0;

    virtual void setMessage(void* pMessage) = 0;

    virtual void setDestination(PipelineStage destination) = 0;

    virtual PipelineStage getDestination() const = 0;
};
}  // namespace sc

#endif
