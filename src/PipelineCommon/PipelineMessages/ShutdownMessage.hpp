#pragma once

#include <memory>

#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineIdentifiers.hpp"

namespace pipeline
{
class ShutdownMessage : public BasePipelineMessage
{
  public:
    ShutdownMessage();

    ShutdownMessage(uint32_t source, uint32_t destination, uint32_t messageNumber);

    virtual ~ShutdownMessage() = default;

    /// @brief This method does nothing for ShutdownMessage
    virtual void setOwnedData(std::unique_ptr<BasePipelineData>& pPipelineData) noexcept override;

    /// @brief This method does nothing for ShutdownMessage
    virtual std::unique_ptr<BasePipelineData>& getOwnedData() noexcept override;

    /// @brief This method returns a nullptr
    virtual BasePipelineData* releaseOwnedData() noexcept override;

    /// @brief This method does nothing for ShutdownMessage
    virtual void deleteOwnedData() noexcept override;

    /// Deleted to prevent misuse
    ShutdownMessage(const ShutdownMessage&) = delete;
    ShutdownMessage(const ShutdownMessage&&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&&) = delete;

  private:
    std::unique_ptr<BasePipelineData> pNullPipelineData_;
};

}  // namespace pipeline
