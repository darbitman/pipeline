#ifndef VERTICALSEAMCARVERPIPELINEBUILDER_HPP
#define VERTICALSEAMCARVERPIPELINEBUILDER_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include "IPipelineInterface.hpp"
#include "IPipelineStage.hpp"
#include "IPipelineStageBuilder.hpp"
#include "PipelineSenderReceiver.hpp"

namespace sc
{
class VerticalSeamCarverPipelineBuilder : public IPipelineStageBuilder
{
  public:
    explicit VerticalSeamCarverPipelineBuilder(PipelineSenderReceiver* pSenderReceiver);

    virtual ~VerticalSeamCarverPipelineBuilder() = default;

    virtual void createPipeline() override;

    virtual std::unique_ptr<IPipelineStage> createNewStage(EPipelineStageId stageId, EPipelineQueueType queueType) override;

    virtual std::unique_ptr<IPipelineInterface>& createPipelineInterface() override;

    virtual std::vector<std::unique_ptr<IPipelineStage>>* getStages(
        EPipelineStageId stageId) const override;

  private:
    bool bPipelineCreated_;

    std::unordered_map<EPipelineStageId,
                       std::unique_ptr<std::vector<std::unique_ptr<IPipelineStage>>>>
        stageIdToVectorOfPipelineStages_;

    std::unique_ptr<std::vector<std::vector<std::unique_ptr<IPipelineStage>>>> pPipelineStages_;

    std::unique_ptr<IPipelineInterface> pPipelineInterface_;

    PipelineSenderReceiver* pSenderReceiver_;

    void createStage(EPipelineStageId stageId, EPipelineQueueType queueType);
};
}  // namespace sc

#endif
