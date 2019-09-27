#pragma once

#include <memory>
#include <vector>

#include "IPipelineInterface.hpp"
#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class IPipelineStageBuilder
{
  public:
    virtual ~IPipelineStageBuilder() = 0;

    virtual void createPipeline() = 0;

    virtual std::unique_ptr<IPipelineStage> createNewStage(EComponentId stageId,
                                                           EComponentLinkType queueType) = 0;

    virtual std::unique_ptr<IPipelineInterface>& createPipelineInterface() = 0;

    virtual std::vector<std::unique_ptr<IPipelineStage>>* getStages(EComponentId stageId) const = 0;
};

}  // namespace sc
