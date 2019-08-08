#ifndef BASEPIPELINEMESSAGE_HPP
#define BASEPIPELINEMESSAGE_HPP

#include <cstdint>

#include "PipelineCommon.hpp"

namespace sc
{
class BasePipelineMessage
{
  public:
    virtual ~BasePipelineMessage() = 0;

    virtual EPipelineMessageType getMessageType() const = 0;

    virtual void* getMessage() const = 0;

    virtual void setMessage(void* pMessage) = 0;

    virtual void setDestination(EPipelineStageId destination) = 0;

    virtual EPipelineStageId getDestination() const = 0;

    virtual void setMessageNumber(int32_t newMessageNumber) = 0;

    virtual int32_t getMessageNumber() const = 0;
};
}  // namespace sc

#endif
