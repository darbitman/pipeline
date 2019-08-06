#ifndef PIPELINEDATAMESSAGE_HPP
#define PIPELINEDATAMESSAGE_HPP

#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineMessageType.hpp"
#include "StageNumbers.hpp"

namespace sc
{
class PipelineDataMessage : public BasePipelineMessage
{
  public:
    explicit PipelineDataMessage(PipelineStage destination, BasePipelineData* pMessage);

    ~PipelineDataMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    virtual void setDestination(PipelineStage destination) override;

    virtual PipelineStage getDestination() const override;

    // deleted to prevent misuse
    PipelineDataMessage(const PipelineDataMessage&) = delete;
    PipelineDataMessage(const PipelineDataMessage&&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;

    PipelineStage destination_;

    void* pMessage_;
};
}  // namespace sc

#endif
