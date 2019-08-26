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


bool SeamCarverProcessorFactory::registerNewStage(EPipelineStageId stageId,
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

bool SeamCarverProcessorFactory::isStageRegistered(EPipelineStageId stageId)
{
    return (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0);
}

unique_ptr<ISeamCarverDataProcessor> SeamCarverProcessorFactory::createStage(
    EPipelineStageId stageId)
{
    unique_ptr<ISeamCarverDataProcessor> p_new_stage(nullptr);

    if (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0)
    {
        p_new_stage = stageIdToCreateProcessorFunctionMap_.at(stageId)();
    }

    return p_new_stage;
}

unique_ptr<vector<EPipelineStageId>> SeamCarverProcessorFactory::getVectorOfRegisteredStages()
{
    auto pStageIds = make_unique<vector<EPipelineStageId>>();

    auto iter = stageIdToCreateProcessorFunctionMap_.begin();
    auto iterEnd = stageIdToCreateProcessorFunctionMap_.end();

    for (; iter != iterEnd; ++iter)
    {
        pStageIds->push_back(iter->first);
    }

    return pStageIds;
}

}  // namespace sc
