#include "SeamCarverStageFactory.hpp"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"

using std::shared_ptr;
using namespace sc;

SeamCarverStageFactory& SeamCarverStageFactory::getFactoryInstance()
{
    static SeamCarverStageFactory factory;
    return factory;
}

void SeamCarverStageFactory::registerNewStage(uint32_t stage_id, createStageFunction function)
{
    // check if map doesn't have the mapping already
    if (stage_id_to_createstagefunc_map_.count(stage_id) == 0)
    {
        stage_id_to_createstagefunc_map_[stage_id] = function;
    }
}

shared_ptr<IPipelineStage> SeamCarverStageFactory::createStage(
    EPipelineStageId stage_id, shared_ptr<PipelineSenderReceiver> pSenderReceiver)
{
    shared_ptr<IPipelineStage> p_new_stage(nullptr);

    if (stage_id_to_createstagefunc_map_.count(stage_id) > 0)
    {
        auto stageCreateFunction = stage_id_to_createstagefunc_map_[stage_id];
        p_new_stage = stageCreateFunction(pSenderReceiver);
    }

    return p_new_stage;
}
