#include "SeamCarverProcessorFactory.hpp"

#include <memory>
#include <vector>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineIdentifiers.hpp"
#include "SeamCarverDataProcessors.hpp"

using std::make_unique;
using std::unique_ptr;
using std::vector;

namespace pipeline
{
bool SeamCarverProcessorFactory::registerComponent(uint32_t stageId,
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

bool SeamCarverProcessorFactory::isComponentRegistered(uint32_t stageId)
{
    return (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0);
}

unique_ptr<ISeamCarverDataProcessor> SeamCarverProcessorFactory::createStage(
    uint32_t stageId)
{
    unique_ptr<ISeamCarverDataProcessor> p_new_stage(nullptr);

    if (stageIdToCreateProcessorFunctionMap_.count(stageId) > 0)
    {
        p_new_stage = stageIdToCreateProcessorFunctionMap_.at(stageId)();
    }

    return p_new_stage;
}

unique_ptr<vector<uint32_t>> SeamCarverProcessorFactory::getVectorOfRegisteredStages()
{
    auto pStageIds = make_unique<vector<uint32_t>>();

    for (auto& stageIdCreateProcessorPair : stageIdToCreateProcessorFunctionMap_)
    {
        pStageIds->push_back(stageIdCreateProcessorPair.first);
    }

    return pStageIds;
}

}  // namespace pipeline
