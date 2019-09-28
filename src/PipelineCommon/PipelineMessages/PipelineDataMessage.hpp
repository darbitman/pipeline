#pragma once

#include <cstdint>
#include <memory>

#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineIdentifiers.hpp"

namespace pipeline
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

    PipelineDataMessage(uint32_t source, uint32_t destination, uint32_t messageNumber);

    PipelineDataMessage(uint32_t source, uint32_t destination, uint32_t messageNumber,
                        std::unique_ptr<BasePipelineData>& pPipelineData);

    virtual ~PipelineDataMessage() = default;

    /// @brief Set the owner of the data to this PipelineDataMessage
    /// @param pPipelineData
    /// Ownership will be released from the unique_ptr passed in, and will be transferred to this
    /// PipelineDataMessage. If this message owns data already, that data will be deleted.
    virtual void setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) noexcept override;

    virtual std::unique_ptr<BasePipelineData>& getOwnedData() noexcept override;

    virtual BasePipelineData* releaseOwnedData() noexcept override;

    virtual void deleteOwnedData() noexcept override;

    /// Deleted to prevent misuse
    PipelineDataMessage(const PipelineDataMessage&) = delete;
    PipelineDataMessage(const PipelineDataMessage&&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&) = delete;
    PipelineDataMessage& operator=(const PipelineDataMessage&&) = delete;

  private:
    std::unique_ptr<BasePipelineData> pPipelineData_;

    static constexpr uint32_t STARTING_MESSAGE_NUMBER{0};
};

}  // namespace pipeline
