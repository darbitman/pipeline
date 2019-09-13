#pragma once

#include <memory>
#include <vector>

#include "IPipelineStage.hpp"
#include "IPipelineStageBuilder.hpp"

namespace sc
{
class SeamCarverPipelineController
{
  public:
    explicit SeamCarverPipelineController(IPipelineStageBuilder* pPipelineBuilder);

    ~SeamCarverPipelineController() = default;

  private:
    std::unique_ptr<std::vector<std::unique_ptr<IPipelineStage>>> pStages_;

    IPipelineStageBuilder* pPipelineBuilder_;
};

}  // namespace sc
