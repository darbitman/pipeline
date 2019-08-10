#include "SeamCarverBaseStage.hpp"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"

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
    auto pSeamCarverData = (VerticalSeamCarverData*)(pData.get());

    pSeamCarverDataProcessor_->runSeamCarverProcessor(pSeamCarverData);
}

}  // namespace sc
