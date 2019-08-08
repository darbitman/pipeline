#ifndef PIPELINEDATAMESSAGE_HPP
#define PIPELINEDATAMESSAGE_HPP

#include <cstdint>
#include <memory>

#include "PipelineCommon.hpp"
#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"

namespace sc
{
class PipelineDataMessage : public BasePipelineMessage
{
  public:
    struct MessageNumberLessComparator
    {
        bool operator()(std::shared_ptr<const BasePipelineMessage> pM1, std::shared_ptr<const BasePipelineMessage> pM2)
        {
            return (pM1->getMessageNumber() < pM2->getMessageNumber());
        }
    };

    PipelineDataMessage(EPipelineStageId destination, BasePipelineData* pMessage);

    ~PipelineDataMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    virtual void setDestination(EPipelineStageId destination) override;

    virtual EPipelineStageId getDestination() const override;

    virtual void setMessageNumber(int32_t newMessageNumber) override;

    virtual int32_t getMessageNumber() const override;

    // deleted to prevent misuse
    PipelineDataMessage(const PipelineDataMessage&) = delete;
    PipelineDataMessage(const PipelineDataMessage&&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;

    EPipelineStageId destination_;

    int32_t messageNumber_;

    void* pMessage_;
};
}  // namespace sc

#endif
