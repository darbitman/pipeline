#ifndef SHUTDOWNMESSAGE_HPP
#define SHUTDOWNMESSAGE_HPP

#include <memory>

#include "BasePipelineData.hpp"
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

    virtual std::shared_ptr<BasePipelineData> getPipelineData() const override;

    virtual void setPipelineData(std::shared_ptr<BasePipelineData> pPipelineData) override;

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
