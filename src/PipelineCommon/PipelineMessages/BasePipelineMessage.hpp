#ifndef BASEPIPELINEMESSAGE_HPP
#define BASEPIPELINEMESSAGE_HPP

#include <cstdint>
#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class BasePipelineMessage
{
  public:
    virtual ~BasePipelineMessage() = 0;

    virtual EPipelineMessageType getMessageType() const = 0;

    virtual std::unique_ptr<BasePipelineData>& getData() = 0;

    virtual BasePipelineData* releasePipelineData() = 0;

    virtual void resetPipelineData() = 0;

    virtual void setPipelineData(std::unique_ptr<BasePipelineData>& pPipelineData) = 0;

    virtual void setSource(EPipelineStageId source) = 0;

    virtual EPipelineStageId getSource() const = 0;

    virtual void setDestination(EPipelineStageId destination) = 0;

    virtual EPipelineStageId getDestination() const = 0;

    virtual void setMessageNumber(int32_t newMessageNumber) = 0;

    virtual int32_t getMessageNumber() const = 0;
};
}  // namespace sc

#endif
