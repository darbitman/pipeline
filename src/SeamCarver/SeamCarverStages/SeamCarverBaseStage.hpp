#pragma once

#include <memory>

#include "BasePipelineStage.hpp"
#include "ISeamCarverDataProcessor.hpp"
#include "PipelineIdentifiers.hpp"
#include "PipelineSenderReceiver.hpp"

namespace pipeline
{
class SeamCarverBaseStage : public BasePipelineStage
{
  public:
    SeamCarverBaseStage(uint32_t thisStageId, uint32_t queueType,
                        PipelineSenderReceiver* pSenderReceiver,
                        std::unique_ptr<ISeamCarverDataProcessor>& pSeamCarverDataProcessor);

    SeamCarverBaseStage(uint32_t thisStageId, uint32_t queueType,
                        PipelineSenderReceiver* pSenderReceiver,
                        std::unique_ptr<ISeamCarverDataProcessor>&& pSeamCarverDataProcessor);

    virtual ~SeamCarverBaseStage() override = default;

    using BasePipelineStage::initialize;
    using BasePipelineStage::isInitialized;
    using BasePipelineStage::isRunning;
    using BasePipelineStage::runStage;
    using BasePipelineStage::stopComponent;

    // deleted to prevent misuse
    SeamCarverBaseStage(const SeamCarverBaseStage&) = delete;
    SeamCarverBaseStage(SeamCarverBaseStage&&) = delete;
    SeamCarverBaseStage& operator=(const SeamCarverBaseStage&) = delete;
    SeamCarverBaseStage& operator=(SeamCarverBaseStage&&) = delete;

  protected:
    virtual void processData(std::unique_ptr<BasePipelineData>& pData) override;

    virtual void processMessage(std::unique_ptr<BasePipelineMessage>& pMessage) override;

  private:
    std::unique_ptr<ISeamCarverDataProcessor> pSeamCarverDataProcessor_;
};
}  // namespace pipeline
