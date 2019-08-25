#ifndef BASESEAMCARVERINTERFACE_HPP
#define BASESEAMCARVERINTERFACE_HPP

#include <opencv2/opencv.hpp>

#include "IPipelineInterface.hpp"
#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SharedContainer.hpp"

namespace sc
{
class BaseSeamCarverInterface : public IPipelineInterface
{
  public:
    BaseSeamCarverInterface(EPipelineQueueType queueType, PipelineSenderReceiver* pSenderReceiver);

    ~BaseSeamCarverInterface();

    virtual void addNewDataToPipeline(std::unique_ptr<BasePipelineData>& pPipelineData) override;

    virtual std::unique_ptr<BasePipelineData> getOutputFromPipeline();

    virtual bool doesNewResultExist() const;

    virtual size_t getNumberOfDataObjectsInPipeline() const;

  private:
    const EPipelineStageId thisStageId_;

    const EPipelineQueueType queueType_;

    size_t totalDatObjectsInPipeline_;

    uint32_t frameNumber_;

    PipelineSenderReceiver* pSenderReceiver_;
};

}  // namespace sc
#endif
