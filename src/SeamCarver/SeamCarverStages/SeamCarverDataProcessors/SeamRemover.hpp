#ifndef SEAMREMOVER_HPP
#define SEAMREMOVER_HPP

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

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    SeamRemover(const SeamRemover&) = delete;
    SeamRemover(SeamRemover&&) = delete;
    SeamRemover& operator=(const SeamRemover&) = delete;
    SeamRemover& operator=(SeamRemover&&) = delete;

  private:
    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_3, []() {
                return std::dynamic_pointer_cast<ISeamCarverDataProcessor>(
                    std::make_shared<SeamRemover>());
            });
};

}  // namespace sc

#endif
