#ifndef SHUTDOWNMESSAGE_HPP
#define SHUTDOWNMESSAGE_HPP

#include "BasePipelineMessage.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class ShutdownMessage : public BasePipelineMessage
{
  public:
    explicit ShutdownMessage(EPipelineStageId destination);

    virtual ~ShutdownMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    virtual void setDestination(EPipelineStageId destination) override;

    virtual EPipelineStageId getDestination() const override;

    virtual void setMessageNumber(int32_t newMessageNumber) override;

    virtual int32_t getMessageNumber() const override;

    // deleted to prevent misuse
    ShutdownMessage(const ShutdownMessage&) = delete;
    ShutdownMessage(const ShutdownMessage&&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;

    EPipelineStageId destination_;

    int32_t messageNumber_;
};
}  // namespace sc

#endif
