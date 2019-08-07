#ifndef SHUTDOWNMESSAGE_HPP
#define SHUTDOWNMESSAGE_HPP

#include "BasePipelineMessage.hpp"
#include "PipelineMessageType.hpp"

namespace sc
{
class ShutdownMessage : public BasePipelineMessage
{
  public:
    explicit ShutdownMessage(int32_t destination);

    virtual ~ShutdownMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    virtual void setDestination(int32_t destination) override;

    virtual int32_t getDestination() const override;

    virtual void setMessageNumber(int32_t newMessageNumber) override;

    virtual int32_t getMessageNumber() const override;

    // deleted to prevent misuse
    ShutdownMessage(const ShutdownMessage&) = delete;
    ShutdownMessage(const ShutdownMessage&&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;

    int32_t destination_;

    int32_t messageNumber_;
};
}  // namespace sc

#endif
