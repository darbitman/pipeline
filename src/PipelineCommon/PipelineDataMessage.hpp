#ifndef PIPELINEDATAMESSAGE_HPP
#define PIPELINEDATAMESSAGE_HPP

#include "BasePipelineMessage.hpp"
#include "PipelineMessageType.hpp"
#include "BasePipelineData.hpp"

namespace sc
{
class PipelineDataMessage : public BasePipelineMessage
{
  public:
    explicit PipelineDataMessage(BasePipelineData* pMessage);

    ~PipelineDataMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    // deleted to prevent misuse
    PipelineDataMessage(const PipelineDataMessage&) = delete;
    PipelineDataMessage(const PipelineDataMessage&&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;

    void* pMessage_;
};
}  // namespace sc

#endif
