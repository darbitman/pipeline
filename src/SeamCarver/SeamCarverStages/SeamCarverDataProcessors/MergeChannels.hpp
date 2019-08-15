#ifndef MERGECHANNELS_HPP
#define MERGECHANNELS_HPP

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

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    MergeChannels(const MergeChannels&) = delete;
    MergeChannels(MergeChannels&&) = delete;
    MergeChannels& operator=(const MergeChannels&) = delete;
    MergeChannels& operator=(MergeChannels&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_4, []() {
                return std::dynamic_pointer_cast<ISeamCarverDataProcessor>(
                    std::make_shared<MergeChannels>());
            });
};

}  // namespace sc

#endif
