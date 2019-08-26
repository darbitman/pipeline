#ifndef SEAMFINDER_HPP
#define SEAMFINDER_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class SeamFinder : public ISeamCarverDataProcessor
{
  public:
    SeamFinder();

    virtual ~SeamFinder();

    virtual void runSeamCarverProcessor(BasePipelineData* pData) override;

    // deleted to prevent misuse
    SeamFinder(const SeamFinder&) = delete;
    SeamFinder(SeamFinder&&) = delete;
    SeamFinder& operator=(const SeamFinder&) = delete;
    SeamFinder& operator=(SeamFinder&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::registerNewStage(
            EPipelineStageId::STAGE_2, []() {
                std::unique_ptr<ISeamCarverDataProcessor> pNewSeamCarverDataProcessor =
                    std::make_unique<SeamFinder>();

                return pNewSeamCarverDataProcessor;
            });
};

}  // namespace sc

#endif
