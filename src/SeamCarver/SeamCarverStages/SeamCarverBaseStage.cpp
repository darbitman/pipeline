#include "SeamCarverBaseStage.hpp"

#include <memory>

#include "PipelineIdentifiers.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::move;
using std::unique_ptr;

namespace pipeline
{
SeamCarverBaseStage::SeamCarverBaseStage(
    uint32_t thisStageId, uint32_t queueType,
    PipelineSenderReceiver* pSenderReceiver,
    unique_ptr<ISeamCarverDataProcessor>& pSeamCarverDataProcessor)
    : BasePipelineStage(thisStageId, queueType, pSenderReceiver),
      pSeamCarverDataProcessor_(move(pSeamCarverDataProcessor))
{
}

SeamCarverBaseStage::SeamCarverBaseStage(
    uint32_t thisStageId, uint32_t queueType,
    PipelineSenderReceiver* pSenderReceiver,
    unique_ptr<ISeamCarverDataProcessor>&& pSeamCarverDataProcessor)
    : BasePipelineStage(thisStageId, queueType, pSenderReceiver),
      pSeamCarverDataProcessor_(move(pSeamCarverDataProcessor))
{
}

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
        processData(pMessage->getOwnedData());
    }
}

}  // namespace pipeline
