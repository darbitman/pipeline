#ifndef VERTICALSEAMCARVERPIPELINEBUILDER_HPP
#define VERTICALSEAMCARVERPIPELINEBUILDER_HPP

#include <memory>
#include <vector>

#include "PipelineSenderReceiver.hpp"
#include "IPipelineInterface.hpp"
#include "IPipelineStage.hpp"
#include "IPipelineStageBuilder.hpp"

namespace sc
{
class VerticalSeamCarverPipelineBuilder : public IPipelineStageBuilder
{
  public:
    explicit VerticalSeamCarverPipelineBuilder(std::shared_ptr<);

    virtual ~VerticalSeamCarverPipelineBuilder();

    virtual std::shared_ptr<std::vector<std::vector<std::shared_ptr<IPipelineStage>>>>
    createPipeline() override;

    virtual std::shared_ptr<IPipelineInterface> createPipelineInterface() override;

  private:
    std::shared_ptr<std::vector<std::vector<std::shared_ptr<IPipelineStage>>>> pPipelineStages_;

    std::shared_ptr<IPipelineInterface> pPipelineInterface_;
};
}  // namespace sc

#endif
