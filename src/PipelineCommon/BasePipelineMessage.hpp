#ifndef BASEPIPELINEMESSAGE_HPP
#define BASEPIPELINEMESSAGE_HPP

#include "PipelineMessageType.hpp"

namespace sc
{
class BasePipelineMessage
{
  public:
    virtual ~BasePipelineMessage() = 0;

    virtual EPipelineMessageType getMessageType() const = 0;

    virtual void* getMessage() const = 0;

    virtual void setMessage(void* pMessage) = 0;
};
}  // namespace sc

#endif
