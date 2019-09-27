#pragma once

#include <memory>
#include <vector>

#include "IPipelineInterface.hpp"
#include "IPipelineStage.hpp"
#include "PipelineIdentifiers.hpp"

namespace sc
{
class IPipelineStageBuilder
{
  public:
    virtual ~IPipelineStageBuilder() = 0;

    virtual void createPipeline() = 0;

    virtual std::unique_ptr<IPipelineStage> createNewStage(uint32_t stageId,
                                                           uint32_t queueType) = 0;

    virtual std::unique_ptr<IPipelineInterface>& createPipelineInterface() = 0;

    virtual std::vector<std::unique_ptr<IPipelineStage>>* getStages(uint32_t stageId) const = 0;
};

}  // namespace sc
