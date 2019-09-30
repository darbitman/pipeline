#include "DefaultPipelineBuilder.hpp"

#include <utility>

#include "DataProcessorManager.hpp"
#include "IDataProcessor.hpp"
#include "IMessageRouter.hpp"
#include "IPipelineStage.hpp"
#include "PipelineStageBase.hpp"

using std::make_unique;
using std::move;
using std::unique_ptr;

namespace pipeline
{
DefaultPipelineBuilder::DefaultPipelineBuilder(DataProcessorManager* pDataProcessorManager,
                                               IMessageRouter* pMessageRouter) noexcept
    : pDataProcessorManager_(pDataProcessorManager), pMessageRouter_(pMessageRouter)
{
}

void DefaultPipelineBuilder::addNewComponent(uint32_t stageNumber) noexcept
{
    unique_ptr<IPipelineStage> pNewComponent = make_unique<PipelineStageBase>(
        stageNumber, stageNumber + 1, ComponentLinkType::QUEUE_TYPE_FIFO,
        pDataProcessorManager_->getDataProcessor(stageNumber), pMessageRouter_);

    try
    {
        addTheNewComponent(stageNumber, pNewComponent);
    }
    catch (const std::out_of_range& e)
    {
        // resize pipeline_
        // retry addTheNewComponent
    }
}

const std::vector<std::vector<std::unique_ptr<IPipelineStage>>>& DefaultPipelineBuilder::getStages()
    const noexcept
{
    return pipeline_;
}

const std::vector<std::unique_ptr<IPipelineStage>>& DefaultPipelineBuilder::getParallelComponents(
    uint32_t stageNumber) const
{
    try
    {
        return pipeline_.at(stageNumber);
    }
    catch (const std::out_of_range& e)
    {
        throw;
    }
}

size_t DefaultPipelineBuilder::getNumberOfStages() const noexcept { return pipeline_.size(); }

size_t DefaultPipelineBuilder::getNumberOfParallelComponents(uint32_t stageNumber) const noexcept
{
    try
    {
        return pipeline_.at(stageNumber).size();
    }
    catch (const std::out_of_range& e)
    {
        return 0;
    }
}

void DefaultPipelineBuilder::addTheNewComponent(uint32_t stageNumber,
                                                unique_ptr<IPipelineStage>& pStageToAdd)
{
    try
    {
        pipeline_.at(stageNumber).push_back(move(pStageToAdd));
    }
    catch (const std::out_of_range& e)
    {
        throw;
    }
}

}  // namespace pipeline