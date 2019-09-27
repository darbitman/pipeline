#include "SeamCarverProcessorFactory.hpp"

#include <memory>
#include <vector>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineCommon.hpp"
#include "SeamCarverDataProcessors.hpp"

using std::make_unique;
using std::unique_ptr;
using std::vector;

namespace sc
{
bool SeamCarverProcessorFactory::registerNewStage(EComponentId stageId,
                                                  createProcessorFunction function)
{
    // check if map doesn't have the mapping already
    if (stageIdToCreateProcessorFunctionMap_.count(stageId) == 0)
    {
        stageIdToCreateProcessorFunctionMap_[stageId] = function;
        return true;
    }
    return false;
}

bool SeamCarverProcessorFactory::isStageRegistered(EComponentId stageId)
{
    return (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0);
}

unique_ptr<ISeamCarverDataProcessor> SeamCarverProcessorFactory::createStage(
    EComponentId stageId)
{
    unique_ptr<ISeamCarverDataProcessor> p_new_stage(nullptr);

    if (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0)
    {
        p_new_stage = stageIdToCreateProcessorFunctionMap_.at(stageId)();
    }

    return p_new_stage;
}

unique_ptr<vector<EComponentId>> SeamCarverProcessorFactory::getVectorOfRegisteredStages()
{
    auto pStageIds = make_unique<vector<EComponentId>>();

    for (auto& stageIdCreateProcessorPair : stageIdToCreateProcessorFunctionMap_)
    {
        pStageIds->push_back(stageIdCreateProcessorPair.first);
    }

    return pStageIds;
}

}  // namespace sc
