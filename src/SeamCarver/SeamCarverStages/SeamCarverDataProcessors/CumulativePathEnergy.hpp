#ifndef CUMULATIVEPATHENERGY_HPP
#define CUMULATIVEPATHENERGY_HPP

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class CumulativePathEnergy : public ISeamCarverDataProcessor
{
  public:
    CumulativePathEnergy();

    virtual ~CumulativePathEnergy();

    virtual void runSeamCarverProcessor(BasePipelineData* pData) override;

    // deleted to prevent misuse
    CumulativePathEnergy(const CumulativePathEnergy&) = delete;
    CumulativePathEnergy(CumulativePathEnergy&&) = delete;
    CumulativePathEnergy& operator=(const CumulativePathEnergy&) = delete;
    CumulativePathEnergy& operator=(CumulativePathEnergy&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::registerNewStage(
            EPipelineStageId::STAGE_1, []() {
                std::unique_ptr<ISeamCarverDataProcessor> pNewSeamCarverDataProcessor =
                    std::make_unique<CumulativePathEnergy>();

                return pNewSeamCarverDataProcessor;
            });
};

}  // namespace sc

#endif
