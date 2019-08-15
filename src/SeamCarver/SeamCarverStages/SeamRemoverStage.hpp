#ifndef SEAMREMOVERSTAGE_HPP
#define SEAMREMOVERSTAGE_HPP

#include <memory>

#include "BasePipelineStage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SeamCarverStageFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class SeamRemoverStage : public BasePipelineStage
{
  public:
    explicit SeamRemoverStage(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~SeamRemoverStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    SeamRemoverStage(const SeamRemoverStage&) = delete;
    SeamRemoverStage(SeamRemoverStage&&) = delete;
    SeamRemoverStage& operator=(const SeamRemoverStage&) = delete;
    SeamRemoverStage& operator=(SeamRemoverStage&&) = delete;

  protected:
    /**
     * @brief method that does the actual data processing
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData) override;

  private:
    void removeSeams(VerticalSeamCarverData* data);

    inline static const bool bRegistered_ =
        SeamCarverStageFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_3, [](std::shared_ptr<PipelineSenderReceiver> pSenderReceiver) {
                return std::dynamic_pointer_cast<IPipelineStage>(
                    std::make_shared<SeamRemoverStage>(pSenderReceiver));
            });
};
}  // namespace sc

#endif
