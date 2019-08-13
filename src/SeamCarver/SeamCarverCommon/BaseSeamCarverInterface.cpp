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
using std::make_shared;
using std::shared_ptr;

namespace sc
{
BaseSeamCarverInterface::BaseSeamCarverInterface(EPipelineQueueType queueType,
                                                 shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : thisStageId_(EPipelineStageId::INTERFACE_STAGE),
      queueType_(queueType),
      totalDatObjectsInPipeline_(0),
      frameNumber_(0),
      pSenderReceiver_(pSenderReceiver)
{
}

BaseSeamCarverInterface::~BaseSeamCarverInterface() {}

void BaseSeamCarverInterface::addNewDataToPipeline(shared_ptr<BasePipelineData> pPipelineData)
{
    if (pSenderReceiver_ != nullptr)
    {
        // create a new message to hold the BasePipelineData
        auto pMessage = make_shared<PipelineDataMessage>(thisStageId_, EPipelineStageId::STAGE_0,
                                                         pPipelineData);

        pSenderReceiver_->send(pMessage);
    }
}

shared_ptr<BasePipelineData> BaseSeamCarverInterface::getOutputFromPipeline()
{
    if (doesNewResultExist())
    {
        return pSenderReceiver_->receive(thisStageId_)->getPipelineData();
    }
    else
    {
        return nullptr;
    }
}

bool BaseSeamCarverInterface::doesNewResultExist() const
{
    return pSenderReceiver_->canReceive(thisStageId_);
}

size_t BaseSeamCarverInterface::getNumberOfDataObjectsInPipeline() const
{
    return totalDatObjectsInPipeline_;
}

}  // namespace sc