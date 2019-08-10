#ifndef SEAMCARVERBASESTAGE_HPP
#define SEAMCARVERBASESTAGE_HPP

#include <memory>

#include "BasePipelineStage.hpp"
#include "ISeamCarverDataProcessor.hpp"
#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"

namespace sc
{
class SeamCarverBaseStage : public BasePipelineStage
{
  public:
    SeamCarverBaseStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                        std::shared_ptr<PipelineSenderReceiver> pSenderReceiver,
                        std::shared_ptr<ISeamCarverDataProcessor> pSeamCarverDataProcessor);

    virtual ~SeamCarverBaseStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    SeamCarverBaseStage(const SeamCarverBaseStage&) = delete;
    SeamCarverBaseStage(SeamCarverBaseStage&&) = delete;
    SeamCarverBaseStage& operator=(const SeamCarverBaseStage&) = delete;
    SeamCarverBaseStage& operator=(SeamCarverBaseStage&&) = delete;

  protected:
    /**
     * @brief method that calls the SeamCarverDataProcessor
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData);

  private:
    std::shared_ptr<ISeamCarverDataProcessor> pSeamCarverDataProcessor_;
};
}  // namespace sc

#endif
