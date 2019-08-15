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

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    CumulativePathEnergy(const CumulativePathEnergy&) = delete;
    CumulativePathEnergy(CumulativePathEnergy&&) = delete;
    CumulativePathEnergy& operator=(const CumulativePathEnergy&) = delete;
    CumulativePathEnergy& operator=(CumulativePathEnergy&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_1, []() {
                return std::dynamic_pointer_cast<ISeamCarverDataProcessor>(
                    std::make_shared<CumulativePathEnergy>());
            });
};

}  // namespace sc

#endif
