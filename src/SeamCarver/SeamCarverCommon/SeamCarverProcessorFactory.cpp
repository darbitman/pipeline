#include "SeamCarverProcessorFactory.hpp"

#include <memory>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineCommon.hpp"

using std::shared_ptr;
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

}  // namespace sc
