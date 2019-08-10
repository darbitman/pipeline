#ifndef BASESEAMCARVERINTERFACE_HPP
#define BASESEAMCARVERINTERFACE_HPP

#include <opencv2/opencv.hpp>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SharedContainer.hpp"

namespace sc
{
class BaseSeamCarverInterface
{
  public:
    BaseSeamCarverInterface(EPipelineQueueType queueType,
                            std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    ~BaseSeamCarverInterface();

    virtual void addNewDataToPipeline(std::shared_ptr<cv::Mat> pNewFrame, size_t numSeamsToRemove);

    virtual std::shared_ptr<cv::Mat> getOutputFrameFromPipeline();

    virtual bool doesNewResultExist() const;

    virtual size_t getNumberOfDataObjectsInPipeline() const;

  private:
    const EPipelineStageId thisStageId_;

    const EPipelineQueueType queueType_;

    size_t totalDatObjectsInPipeline_;

    uint32_t frameNumber_;

    std::shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    std::shared_ptr<SharedContainer<std::shared_ptr<BasePipelineData>>> pFreestoreQueue_;
};
}  // namespace sc
#endif
