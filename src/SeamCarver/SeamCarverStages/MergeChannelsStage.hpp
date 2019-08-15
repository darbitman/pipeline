#ifndef MERGECHANNELSSTAGE_HPP
#define MERGECHANNELSSTAGE_HPP

#include <memory>

#include "BasePipelineStage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"
#include "SeamCarverStageFactory.hpp"

namespace sc
{
class MergeChannelsStage : public BasePipelineStage
{
  public:
    explicit MergeChannelsStage(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~MergeChannelsStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    MergeChannelsStage(const MergeChannelsStage&) = delete;
    MergeChannelsStage(MergeChannelsStage&&) = delete;
    MergeChannelsStage& operator=(const MergeChannelsStage&) = delete;
    MergeChannelsStage& operator=(MergeChannelsStage&&) = delete;

  protected:
    /**
     * @brief method that does the actual data processing
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData) override;

  private:
    void mergeChannels(VerticalSeamCarverData* data);

        inline static const bool bRegistered_ =
        SeamCarverStageFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_4, [](std::shared_ptr<PipelineSenderReceiver> pSenderReceiver) {
                return std::dynamic_pointer_cast<IPipelineStage>(
                    std::make_shared<MergeChannelsStage>(pSenderReceiver));
            });
};
}  // namespace sc

#endif
