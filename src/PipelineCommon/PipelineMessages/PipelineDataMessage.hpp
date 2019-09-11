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
        bool operator()(std::unique_ptr<BasePipelineMessage>& pM1,
                        std::unique_ptr<BasePipelineMessage>& pM2)
        {
            return (pM1->getMessageNumber() < pM2->getMessageNumber());
        }
    };

    PipelineDataMessage();

    PipelineDataMessage(EPipelineStageId source, EPipelineStageId destination,
                        uint32_t messageNumber);

    PipelineDataMessage(EPipelineStageId source, EPipelineStageId destination,
                        uint32_t messageNumber, std::unique_ptr<BasePipelineData>& pPipelineData);

    virtual ~PipelineDataMessage() = default;

    /// @brief Set the owner of the data to this PipelineDataMessage
    /// @param pPipelineData
    /// Ownership will be released from the unique_ptr passed in, and will be transferred to this
    /// PipelineDataMessage. If this message owns data already, that data will be deleted.
    virtual void setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) override;

    virtual std::unique_ptr<BasePipelineData>& getOwnedData() override;

    virtual BasePipelineData* releaseOwnedData() override;

    virtual void deleteOwnedData() override;

    /// Deleted to prevent misuse
    PipelineDataMessage(const PipelineDataMessage&) = delete;
    PipelineDataMessage(const PipelineDataMessage&&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&&) = delete;

  private:
    std::unique_ptr<BasePipelineData> pPipelineData_;
};

}  // namespace sc

#endif
