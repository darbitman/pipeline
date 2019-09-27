#pragma once

#include <memory>

#include "BasePipelineData.hpp"
#include "BasePipelineMessage.hpp"
#include "PipelineIdentifiers.hpp"

namespace sc
{
class ShutdownMessage : public BasePipelineMessage
{
  public:
    ShutdownMessage();

    ShutdownMessage(uint32_t source, uint32_t destination, uint32_t messageNumber);

    virtual ~ShutdownMessage();

    /// @brief This call does nothing for ShutdownMessage
    virtual void setOwnedData([
        [maybe_unused]] std::unique_ptr<BasePipelineData>& pPipelineData) override;

    /// @brief this call does nothing for ShutdownMessage
    virtual std::unique_ptr<BasePipelineData>& getOwnedData() override;

    virtual BasePipelineData* releaseOwnedData() override;

    virtual void deleteOwnedData() override;

    /// Deleted to prevent misuse
    ShutdownMessage(const ShutdownMessage&) = delete;
    ShutdownMessage(const ShutdownMessage&&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&) = delete;
    ShutdownMessage& operator=(const ShutdownMessage&&) = delete;

  private:
    std::unique_ptr<BasePipelineData> pNullPipelineData_;
};

}  // namespace sc
