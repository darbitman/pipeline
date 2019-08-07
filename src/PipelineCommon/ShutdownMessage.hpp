#ifndef SHUTDOWNMESSAGE_HPP
#define SHUTDOWNMESSAGE_HPP

#include "BasePipelineMessage.hpp"
#include "PipelineMessageType.hpp"

namespace sc
{
class ShutdownMessage : public BasePipelineMessage
{
  public:
    ShutdownMessage();

    virtual ~ShutdownMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    virtual void setDestination(int32_t destination) override;

    virtual int32_t getDestination() const override;

    // deleted to prevent misuse
    ShutdownMessage(const ShutdownMessage&) = delete;
    ShutdownMessage(const ShutdownMessage&&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;
};
}  // namespace sc

#endif
