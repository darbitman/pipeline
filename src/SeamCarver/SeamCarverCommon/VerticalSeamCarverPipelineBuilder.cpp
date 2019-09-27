#include "VerticalSeamCarverPipelineBuilder.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "BaseSeamCarverInterface.hpp"
#include "IPipelineStage.hpp"
#include "PipelineIdentifiers.hpp"
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
    createStage(ComponentId::STAGE_0, ComponentLinkType::QUEUE_TYPE_FIFO);
    createStage(ComponentId::STAGE_1, ComponentLinkType::QUEUE_TYPE_FIFO);
    createStage(ComponentId::STAGE_2, ComponentLinkType::QUEUE_TYPE_FIFO);
    createStage(ComponentId::STAGE_3, ComponentLinkType::QUEUE_TYPE_FIFO);
    createStage(ComponentId::STAGE_4, ComponentLinkType::QUEUE_TYPE_FIFO);
}

unique_ptr<IPipelineInterface>& VerticalSeamCarverPipelineBuilder::createPipelineInterface()
{
    if (pPipelineInterface_ == nullptr)
    {
        pPipelineInterface_ = make_unique<BaseSeamCarverInterface>(
            ComponentLinkType::QUEUE_TYPE_FIFO, pSenderReceiver_);
    }

    return pPipelineInterface_;
}

vector<unique_ptr<IPipelineStage>>* VerticalSeamCarverPipelineBuilder::getStages(
    uint32_t stageId) const
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

void VerticalSeamCarverPipelineBuilder::createStage(uint32_t stageId,
                                                    uint32_t queueType)
{
    // create a vector if it hasn't been used before
    if (stageIdToVectorOfPipelineStages_.count(stageId) == 0)
    {
        stageIdToVectorOfPipelineStages_.insert(
            make_pair<uint32_t, unique_ptr<vector<unique_ptr<IPipelineStage>>>>(
                move(stageId), make_unique<vector<unique_ptr<IPipelineStage>>>()));
    }

    if (auto pProcessor = SeamCarverProcessorFactory::createStage(stageId); pProcessor != nullptr)
    {
        unique_ptr<IPipelineStage> pBaseStage =
            make_unique<SeamCarverBaseStage>(stageId, queueType, pSenderReceiver_, pProcessor);

        stageIdToVectorOfPipelineStages_[stageId]->push_back(move(pBaseStage));
    }
}
