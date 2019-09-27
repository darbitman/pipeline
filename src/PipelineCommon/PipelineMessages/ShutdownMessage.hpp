
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
    ShutdownMessage();

    ShutdownMessage(EComponentId source, EComponentId destination, uint32_t messageNumber);

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

#endif
