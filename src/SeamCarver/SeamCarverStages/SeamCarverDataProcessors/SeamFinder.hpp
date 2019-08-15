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

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    SeamFinder(const SeamFinder&) = delete;
    SeamFinder(SeamFinder&&) = delete;
    SeamFinder& operator=(const SeamFinder&) = delete;
    SeamFinder& operator=(SeamFinder&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_2, []() {
                return std::dynamic_pointer_cast<ISeamCarverDataProcessor>(
                    std::make_shared<SeamFinder>());
            });
};

}  // namespace sc

#endif
