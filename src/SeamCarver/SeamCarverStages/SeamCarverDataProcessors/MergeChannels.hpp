#pragma once

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class MergeChannels : public ISeamCarverDataProcessor
{
  public:
    MergeChannels();

    virtual ~MergeChannels();

    virtual void runSeamCarverProcessor(BasePipelineData* pData) override;

    // deleted to prevent misuse
    MergeChannels(const MergeChannels&) = delete;
    MergeChannels(MergeChannels&&) = delete;
    MergeChannels& operator=(const MergeChannels&) = delete;
    MergeChannels& operator=(MergeChannels&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::registerNewStage(
            EComponentId::STAGE_4, []() {
                std::unique_ptr<ISeamCarverDataProcessor> pNewSeamCarverDataProcessor =
                    std::make_unique<MergeChannels>();

                return pNewSeamCarverDataProcessor;
            });
};

}  // namespace sc
