#include "SeamCarverBaseStage.hpp"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::shared_ptr;

namespace sc
{
SeamCarverBaseStage::SeamCarverBaseStage(
    EPipelineStageId thisStageId, EPipelineQueueType queueType,
    shared_ptr<PipelineSenderReceiver> pSenderReceiver,
    std::shared_ptr<ISeamCarverDataProcessor> pSeamCarverDataProcessor)
    : BasePipelineStage(thisStageId, queueType, pSenderReceiver),
      pSeamCarverDataProcessor_(pSeamCarverDataProcessor)
{
}

SeamCarverBaseStage::~SeamCarverBaseStage() {}

void SeamCarverBaseStage::initialize() { BasePipelineStage::initialize(); }

void SeamCarverBaseStage::runStage() { BasePipelineStage::runStage(); }

void SeamCarverBaseStage::stopStage() { BasePipelineStage::stopStage(); }

bool SeamCarverBaseStage::isInitialized() const { return BasePipelineStage::isInitialized(); }

bool SeamCarverBaseStage::isRunning() const { return BasePipelineStage::isRunning(); }

void SeamCarverBaseStage::processData(shared_ptr<BasePipelineData> pData)
{
    if (pSeamCarverDataProcessor_ != nullptr)
    {
        pSeamCarverDataProcessor_->runSeamCarverProcessor(
            dynamic_pointer_cast<VerticalSeamCarverData>(pData));
    }
}

void SeamCarverBaseStage::processMessage(shared_ptr<BasePipelineMessage> pMessage)
{
    if (pMessage == nullptr || pSeamCarverDataProcessor_ == nullptr)
    {
        return;
    }
    else
    {
        auto pData = dynamic_pointer_cast<VerticalSeamCarverData>(pMessage->getPipelineData());
    }
}

}  // namespace sc
