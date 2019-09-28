#pragma once

#include <memory>

#include "BasePipelineData.hpp"
#include "PipelineMessageBase.hpp"
#include "PipelineIdentifiers.hpp"

namespace pipeline
{
class PipelineShutdownMessage : public PipelineMessageBase
{
  public:
    PipelineShutdownMessage();

    PipelineShutdownMessage(uint32_t source, uint32_t destination, uint32_t messageNumber);

    virtual ~PipelineShutdownMessage() = default;

    /// @brief This method does nothing for PipelineShutdownMessage
    virtual void setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) noexcept override;

    /// @brief This method does nothing for PipelineShutdownMessage
    virtual std::unique_ptr<BasePipelineData>& getOwnedData() noexcept override;

    /// @brief This method returns a nullptr
    virtual BasePipelineData* releaseOwnedData() noexcept override;

    /// @brief This method does nothing for PipelineShutdownMessage
    virtual void deleteOwnedData() noexcept override;

    /// Deleted to prevent misuse
    PipelineShutdownMessage(const PipelineShutdownMessage&) = delete;
    PipelineShutdownMessage(const PipelineShutdownMessage&&) = delete;
    PipelineShutdownMessage& operator=(const PipelineShutdownMessage&) = delete;
    PipelineShutdownMessage& operator=(const PipelineShutdownMessage&&) = delete;

  private:
    std::unique_ptr<BasePipelineData> pNullPipelineData_;
};

}  // namespace pipeline
