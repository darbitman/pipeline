#pragma once

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
    BaseSeamCarverInterface(EComponentLinkType queueType, PipelineSenderReceiver* pSenderReceiver);

    ~BaseSeamCarverInterface() = default;

    /// @brief
    /// @param pPipelineData This unique_ptr will no longer be the owner of the BasePipelineData. It
    /// will be a nullptr.
    virtual void addNewDataToPipeline(std::unique_ptr<BasePipelineData>& pPipelineData) override;

    virtual std::unique_ptr<BasePipelineData> getOutputFromPipeline();

    virtual bool doesNewResultExist() const;

    virtual size_t getNumberOfDataObjectsInPipeline() const;

  private:
    const EComponentId thisStageId_;

    const EComponentLinkType queueType_;

    size_t totalDataObjectsInPipeline_;

    uint32_t frameNumber_;

    PipelineSenderReceiver* pSenderReceiver_;
};

}  // namespace sc
