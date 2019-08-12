#ifndef VERTICALSEAMCARVERPIPELINEBUILDER_HPP
#define VERTICALSEAMCARVERPIPELINEBUILDER_HPP

#include <memory>
#include <vector>

#include "IPipelineInterface.hpp"
#include "IPipelineStageBuilder.hpp"

namespace sc
{
class VerticalSeamCarverPipelineBuilder : public IPipelineStageBuilder
{
  public:
    VerticalSeamCarverPipelineBuilder();

    virtual ~VerticalSeamCarverPipelineBuilder();

    virtual std::shared_ptr<std::vector<std::vector<std::shared_ptr<IPipelineStage>>>>
    createPipeline() override;
    virtual std::shared_ptr<IPipelineInterface> createPipelineInterface() override;

  private:
    bool bPipelineStagesCreated_;

    std::shared_ptr<std::vector<std::vector<std::shared_ptr<IPipelineStage>>>> pPipelineStages_;
};
}  // namespace sc

#endif
