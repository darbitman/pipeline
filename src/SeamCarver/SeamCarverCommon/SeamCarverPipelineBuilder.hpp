#ifndef SEAMCARVERPIPELINEBUILDER_HPP
#define SEAMCARVERPIPELINEBUILDER_HPP

#include <memory>
#include <vector>

#include "IPipelineStageBuilder.hpp"

namespace sc
{
class SeamCarverPipelineBuilder : public IPipelineStageBuilder
{
  public:
    SeamCarverPipelineBuilder();

    virtual ~SeamCarverPipelineBuilder();

    virtual std::shared_ptr<std::vector<std::shared_ptr<IPipelineStage>>> buildPipeline() override;

  private:
};
}  // namespace sc

#endif
