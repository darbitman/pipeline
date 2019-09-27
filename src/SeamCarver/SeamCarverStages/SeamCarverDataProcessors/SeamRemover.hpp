#pragma once

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class SeamRemover : public ISeamCarverDataProcessor
{
  public:
    SeamRemover();

    virtual ~SeamRemover();

    virtual void runSeamCarverProcessor(BasePipelineData* pData) override;

    // deleted to prevent misuse
    SeamRemover(const SeamRemover&) = delete;
    SeamRemover(SeamRemover&&) = delete;
    SeamRemover& operator=(const SeamRemover&) = delete;
    SeamRemover& operator=(SeamRemover&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::registerComponent(EComponentId::STAGE_3, []() {
            std::unique_ptr<ISeamCarverDataProcessor> pNewSeamCarverDataProcessor =
                std::make_unique<SeamRemover>();

            return pNewSeamCarverDataProcessor;
        });
};

}  // namespace sc
