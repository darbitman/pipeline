#include "BaseSeamCarverInterface.hpp"

#include <memory>
#include <opencv2/opencv.hpp>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SharedQueue.hpp"
#include "VerticalSeamCarverData.hpp"

using cv::Mat;
using std::dynamic_pointer_cast;
using std::make_unique;
using std::move;
using std::unique_ptr;

namespace sc
{
BaseSeamCarverInterface::BaseSeamCarverInterface(EComponentLinkType queueType,
                                                 PipelineSenderReceiver* pSenderReceiver)
    : thisStageId_(EComponentId::INTERFACE_STAGE),
      queueType_(queueType),
      totalDataObjectsInPipeline_(0),
      frameNumber_(0),
      pSenderReceiver_(pSenderReceiver)
{
}

void BaseSeamCarverInterface::addNewDataToPipeline(unique_ptr<BasePipelineData>& pPipelineData)
{
    if (pSenderReceiver_ != nullptr)
    {
        // create a new message to hold the BasePipelineData
        unique_ptr<BasePipelineMessage> pMessage = make_unique<PipelineDataMessage>(
            thisStageId_, EComponentId::STAGE_0, frameNumber_++, pPipelineData);

        pSenderReceiver_->send(pMessage);
    }
}

unique_ptr<BasePipelineData> BaseSeamCarverInterface::getOutputFromPipeline()
{
    if (doesNewResultExist())
    {
        auto pReceivedMessage = pSenderReceiver_->receive(thisStageId_);
        return unique_ptr<BasePipelineData>(pReceivedMessage->releaseOwnedData());
    }
    else
    {
        return unique_ptr<BasePipelineData>();
    }
}

bool BaseSeamCarverInterface::doesNewResultExist() const
{
    return pSenderReceiver_->canReceive(thisStageId_);
}

size_t BaseSeamCarverInterface::getNumberOfDataObjectsInPipeline() const
{
    return totalDataObjectsInPipeline_;
}

}  // namespace sc
