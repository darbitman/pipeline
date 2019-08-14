#include "VerticalSeamCarverPipelineBuilder.hpp"

#include <memory>
#include <vector>

#include "BaseSeamCarverInterface.hpp"
#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"
#include "SeamCarverBaseStage.hpp"
#include "SeamCarverProcessorFactory.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace sc
{
VerticalSeamCarverPipelineBuilder::VerticalSeamCarverPipelineBuilder(
    shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : bPipelineCreated_(false), pSenderReceiver_(pSenderReceiver)
{
}

VerticalSeamCarverPipelineBuilder::~VerticalSeamCarverPipelineBuilder() {}

void VerticalSeamCarverPipelineBuilder::createPipeline()
{
    createStage(EPipelineStageId::STAGE_0, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_1, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_2, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_3, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_4, EPipelineQueueType::QUEUE_TYPE_FIFO);
}

shared_ptr<IPipelineInterface> VerticalSeamCarverPipelineBuilder::createPipelineInterface()
{
    if (pPipelineInterface_ == nullptr)
    {
        pPipelineInterface_ = make_shared<BaseSeamCarverInterface>(
            EPipelineQueueType::QUEUE_TYPE_FIFO, pSenderReceiver_);
    }

    return pPipelineInterface_;
}

vector<shared_ptr<IPipelineStage>>* VerticalSeamCarverPipelineBuilder::getStages(
    EPipelineStageId stageId) const
{
    if (stageIdToVectorOfPipelineStages_.count(stageId) == 0)
    {
        return nullptr;
    }
    else
    {
        return stageIdToVectorOfPipelineStages_.at(stageId).get();
    }
}

void VerticalSeamCarverPipelineBuilder::createStage(EPipelineStageId stageId,
                                                    EPipelineQueueType queueType)
{
    auto pProcessor = SeamCarverProcessorFactory::getFactoryInstance().createStage(stageId);

    auto pBaseStage =
        make_shared<SeamCarverBaseStage>(stageId, queueType, pSenderReceiver_, pProcessor);

    // create a vector if it hasn't been used before
    if (stageIdToVectorOfPipelineStages_.count(stageId) == 0)
    {
        stageIdToVectorOfPipelineStages_[stageId] =
            make_shared<vector<shared_ptr<IPipelineStage>>>();
    }

    stageIdToVectorOfPipelineStages_[stageId]->push_back(pBaseStage);
}

}  // namespace sc
