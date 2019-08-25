#include "SeamCarverBaseStage.hpp"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::move;
using std::unique_ptr;

namespace sc
{
SeamCarverBaseStage::SeamCarverBaseStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                                         PipelineSenderReceiver* pSenderReceiver,
                                         unique_ptr<ISeamCarverDataProcessor>& pSeamCarverDataProcessor)
    : BasePipelineStage(thisStageId, queueType, pSenderReceiver),
      pSeamCarverDataProcessor_(move(pSeamCarverDataProcessor))
{
}

SeamCarverBaseStage::~SeamCarverBaseStage() {}

void SeamCarverBaseStage::initialize() { BasePipelineStage::initialize(); }

void SeamCarverBaseStage::runStage() { BasePipelineStage::runStage(); }

void SeamCarverBaseStage::stopStage() { BasePipelineStage::stopStage(); }

bool SeamCarverBaseStage::isInitialized() const { return BasePipelineStage::isInitialized(); }

bool SeamCarverBaseStage::isRunning() const { return BasePipelineStage::isRunning(); }

void SeamCarverBaseStage::processData(std::unique_ptr<BasePipelineData>& pData)
{
    if (pSeamCarverDataProcessor_ != nullptr)
    {
        pSeamCarverDataProcessor_->runSeamCarverProcessor(pData.get());
    }
}

void SeamCarverBaseStage::processMessage(unique_ptr<BasePipelineMessage>& pMessage)
{
    if (pMessage != nullptr && pSeamCarverDataProcessor_ != nullptr)
    {
        processData(pMessage->getData());
    }
}

}  // namespace sc
