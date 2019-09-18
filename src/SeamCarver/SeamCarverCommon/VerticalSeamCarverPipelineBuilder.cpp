#include "VerticalSeamCarverPipelineBuilder.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "BaseSeamCarverInterface.hpp"
#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"
#include "SeamCarverBaseStage.hpp"
#include "SeamCarverProcessorFactory.hpp"

using std::dynamic_pointer_cast;
using std::make_pair;
using std::make_unique;
using std::move;
using std::unique_ptr;
using std::vector;

using namespace sc;

VerticalSeamCarverPipelineBuilder::VerticalSeamCarverPipelineBuilder(
    PipelineSenderReceiver* pSenderReceiver)
    : bPipelineCreated_(false), pSenderReceiver_(pSenderReceiver)
{
}

void VerticalSeamCarverPipelineBuilder::createPipeline()
{
    createStage(EPipelineStageId::STAGE_0, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_1, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_2, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_3, EPipelineQueueType::QUEUE_TYPE_FIFO);
    createStage(EPipelineStageId::STAGE_4, EPipelineQueueType::QUEUE_TYPE_FIFO);
}

unique_ptr<IPipelineInterface>& VerticalSeamCarverPipelineBuilder::createPipelineInterface()
{
    if (pPipelineInterface_ == nullptr)
    {
        pPipelineInterface_ = make_unique<BaseSeamCarverInterface>(
            EPipelineQueueType::QUEUE_TYPE_FIFO, pSenderReceiver_);
    }

    return pPipelineInterface_;
}

vector<unique_ptr<IPipelineStage>>* VerticalSeamCarverPipelineBuilder::getStages(
    EPipelineStageId stageId) const
{
    try
    {
        return stageIdToVectorOfPipelineStages_.at(stageId).get();
    }
    catch (std::out_of_range& e)
    {
        return nullptr;
    }
}

void VerticalSeamCarverPipelineBuilder::createStage(EPipelineStageId stageId,
                                                    EPipelineQueueType queueType)
{
    // create a vector if it hasn't been used before
    if (stageIdToVectorOfPipelineStages_.count(stageId) == 0)
    {
        stageIdToVectorOfPipelineStages_.insert(
            make_pair<EPipelineStageId, unique_ptr<vector<unique_ptr<IPipelineStage>>>>(
                move(stageId), make_unique<vector<unique_ptr<IPipelineStage>>>()));
    }

    if (auto pProcessor = SeamCarverProcessorFactory::createStage(stageId); pProcessor != nullptr)
    {
        unique_ptr<IPipelineStage> pBaseStage =
            make_unique<SeamCarverBaseStage>(stageId, queueType, pSenderReceiver_, pProcessor);

        stageIdToVectorOfPipelineStages_[stageId]->push_back(move(pBaseStage));
    }
}
