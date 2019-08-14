#ifndef IPIPELINESTAGEBUILDER_HPP
#define IPIPELINESTAGEBUILDER_HPP

#include <memory>
#include <vector>

#include "IPipelineInterface.hpp"
#include "IPipelineStage.hpp"

namespace sc
{
class IPipelineStageBuilder
{
  public:
    virtual ~IPipelineStageBuilder();

    virtual void createPipeline() = 0;

    virtual std::shared_ptr<IPipelineInterface> createPipelineInterface() = 0;

    virtual std::vector<std::shared_ptr<IPipelineStage>>* getStages(
        EPipelineStageId stageId) const = 0;
};

}  // namespace sc

#endif
