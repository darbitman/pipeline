#include "SeamCarverProcessorFactory.hpp"

#include <memory>
#include <vector>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineCommon.hpp"

using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace sc
{
SeamCarverProcessorFactory& SeamCarverProcessorFactory::getFactoryInstance()
{
    static SeamCarverProcessorFactory factory;
    return factory;
}

void SeamCarverProcessorFactory::registerNewStage(EPipelineStageId stageId,
                                                  createProcessorFunction function)
{
    // check if map doesn't have the mapping already
    if (stageIdToCreateProcessorFunctionMap_.count(stageId) == 0)
    {
        stageIdToCreateProcessorFunctionMap_[stageId] = function;
    }
}

bool SeamCarverProcessorFactory::isStageRegistered(EPipelineStageId stageId) const
{
    return (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0);
}

shared_ptr<ISeamCarverDataProcessor> SeamCarverProcessorFactory::createStage(
    EPipelineStageId stageId)
{
    shared_ptr<ISeamCarverDataProcessor> p_new_stage(nullptr);

    if (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0)
    {
        auto stageCreateFunction = stageIdToCreateProcessorFunctionMap_[stageId];
        p_new_stage = stageCreateFunction();
    }

    return p_new_stage;
}

shared_ptr<vector<EPipelineStageId>> SeamCarverProcessorFactory::getVectorOfRegisteredStages() const
{
    auto pStageIds = make_shared<vector<EPipelineStageId>>();

    auto iter = stageIdToCreateProcessorFunctionMap_.begin();
    auto iterEnd = stageIdToCreateProcessorFunctionMap_.end();

    for (; iter != iterEnd; ++iter)
    {
        pStageIds->push_back(iter->first);
    }

    return pStageIds;
}

}  // namespace sc
