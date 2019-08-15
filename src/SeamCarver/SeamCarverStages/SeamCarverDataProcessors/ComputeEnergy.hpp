#ifndef COMPUTEENERGY_HPP
#define COMPUTEENERGY_HPP

#include <memory>

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class ComputeEnergy : public ISeamCarverDataProcessor
{
  public:
    ComputeEnergy();

    virtual ~ComputeEnergy();

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    ComputeEnergy(const ComputeEnergy&) = delete;
    ComputeEnergy(ComputeEnergy&&) = delete;
    ComputeEnergy& operator=(const ComputeEnergy&) = delete;
    ComputeEnergy& operator=(ComputeEnergy&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_0, []() {
                return std::dynamic_pointer_cast<ISeamCarverDataProcessor>(
                    std::make_shared<ComputeEnergy>());
            });
};

}  // namespace sc

#endif
