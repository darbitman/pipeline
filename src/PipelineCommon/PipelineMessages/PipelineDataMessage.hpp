#ifndef PIPELINEDATAMESSAGE_HPP
#define PIPELINEDATAMESSAGE_HPP

#include <cstdint>
#include <memory>

#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class PipelineDataMessage : public BasePipelineMessage
{
  public:
    struct MessageNumberLessComparator
    {
        bool operator()(std::shared_ptr<const BasePipelineMessage> pM1,
                        std::shared_ptr<const BasePipelineMessage> pM2)
        {
            return (pM1->getMessageNumber() < pM2->getMessageNumber());
        }
    };

    PipelineDataMessage(EPipelineStageId source, EPipelineStageId destination,
                        std::shared_ptr<BasePipelineData> pPipelineData);

    ~PipelineDataMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual std::shared_ptr<BasePipelineData> getPipelineData() const override;

    virtual void setPipelineData(std::shared_ptr<BasePipelineData> pPipelineData) override;

    virtual void setSource(EPipelineStageId source) override;

    virtual EPipelineStageId getSource() const override;

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

    EPipelineStageId source_;

    EPipelineStageId destination_;

    int32_t messageNumber_;

    std::shared_ptr<BasePipelineData> pPipelineData_;
};

}  // namespace sc

#endif
