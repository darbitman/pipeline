#pragma once

#include <memory>

#include "PipelineDataBase.hpp"
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
    virtual void setOwnedData(std::unique_ptr<PipelineDataBase>& pPipelineData) noexcept override;

    /// @brief This method does nothing for PipelineShutdownMessage
    virtual std::unique_ptr<PipelineDataBase>& getOwnedData() noexcept override;

    /// @brief This method returns a nullptr
    virtual PipelineDataBase* releaseOwnedData() noexcept override;

    /// @brief This method does nothing for PipelineShutdownMessage
    virtual void deleteOwnedData() noexcept override;

    /// Deleted to prevent misuse
    PipelineShutdownMessage(const PipelineShutdownMessage&) = delete;
    PipelineShutdownMessage(const PipelineShutdownMessage&&) = delete;
    PipelineShutdownMessage& operator=(const PipelineShutdownMessage&) = delete;
    PipelineShutdownMessage& operator=(const PipelineShutdownMessage&&) = delete;

  private:
    std::unique_ptr<PipelineDataBase> pNullPipelineData_;
};

}  // namespace pipeline
