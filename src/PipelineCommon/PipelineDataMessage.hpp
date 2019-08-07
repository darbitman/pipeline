#ifndef PIPELINEDATAMESSAGE_HPP
#define PIPELINEDATAMESSAGE_HPP

#include <cstdint>
#include <memory>

#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineMessageType.hpp"
#include "StageNumbers.hpp"

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

    explicit PipelineDataMessage(int32_t destination, BasePipelineData* pMessage);

    ~PipelineDataMessage();

    virtual EPipelineMessageType getMessageType() const override;

    virtual void* getMessage() const override;

    virtual void setMessage(void* pMessage) override;

    virtual void setDestination(int32_t destination) override;

    virtual int32_t getDestination() const override;

    virtual void setMessageNumber(int32_t newMessageNumber) override;

    virtual int32_t getMessageNumber() const override;

    // deleted to prevent misuse
    PipelineDataMessage(const PipelineDataMessage&) = delete;
    PipelineDataMessage(const PipelineDataMessage&&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&&) = delete;

  private:
    EPipelineMessageType messageType_;

    int32_t destination_;

    int32_t messageNumber_;

    void* pMessage_;
};
}  // namespace sc

#endif
