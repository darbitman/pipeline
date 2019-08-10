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
    // create a non blocking freestore queue since this is the only client of that queue
    pFreestoreQueue_ = make_shared<SharedQueue<shared_ptr<BasePipelineData>>>(false);
}

BaseSeamCarverInterface::~BaseSeamCarverInterface() {}

void BaseSeamCarverInterface::addNewDataToPipeline(shared_ptr<Mat> pNewFrame,
                                                   size_t numSeamsToRemove)
{
    // TODO
    // check if pFreestoreQueue_ has available data objects that can be reused
    shared_ptr<VerticalSeamCarverData> pPipelineData;

    if (pFreestoreQueue_->empty())
    {
        pPipelineData = make_shared<VerticalSeamCarverData>();
    }
    else
    {
        pPipelineData = dynamic_pointer_cast<VerticalSeamCarverData>(pFreestoreQueue_->front());
        pFreestoreQueue_->pop();
    }

    while (true)
    {
        // copy image to internal data store
        pPipelineData->saveImage(pNewFrame);

        // // initialize internal data
        // if (pPipelineData->bNeedToInitializeLocalData)
        // {
        //     pPipelineData->initialize();
        //     break;
        // }
        // else
        // {
        //     // check if image is of the same dimension as those used for internal pPipelineData
        //     if (pPipelineData->areImageDimensionsVerified())
        //     {
        //         break;
        //     }
        //     // if image dimensions are different than those of internal pPipelineData,
        //     reinitialize pPipelineData else
        //     {
        //         pPipelineData->bNeedToInitializeLocalData = true;
        //     }
        // }

        // set number of seams to remove for this frame
        // pPipelineData->numSeamsToRemove_ = numSeamsToRemove;

        // reset internal data to 'clean' state
        pPipelineData->resetData();

        // separate individual color channels
        pPipelineData->separateChannels();

        // create new PipelineDataMessage to hold the data
        auto pDataMessage = make_shared<PipelineDataMessage>(
            thisStageId_, EPipelineStageId::STAGE_0, pPipelineData);

        pDataMessage->setMessageNumber(frameNumber_++);

        pSenderReceiver_->send(pDataMessage);

        ++totalDatObjectsInPipeline_;
    }
}

std::shared_ptr<cv::Mat> BaseSeamCarverInterface::getOutputFrameFromPipeline()
{
    // TODO
    return nullptr;
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
