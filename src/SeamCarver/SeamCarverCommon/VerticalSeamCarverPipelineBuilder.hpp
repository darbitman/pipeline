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
    explicit VerticalSeamCarverPipelineBuilder(
        std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~VerticalSeamCarverPipelineBuilder();

    virtual void createPipeline() override;

    virtual std::shared_ptr<IPipelineInterface> createPipelineInterface() override;

    virtual std::vector<std::shared_ptr<IPipelineStage>>* getStages(
        EPipelineStageId stageId) const override;

  private:
    bool bPipelineCreated_;

    std::unordered_map<EPipelineStageId,
                       std::shared_ptr<std::vector<std::shared_ptr<IPipelineStage>>>>
        stageIdToVectorOfPipelineStages_;

    std::shared_ptr<std::vector<std::vector<std::shared_ptr<IPipelineStage>>>> pPipelineStages_;

    std::shared_ptr<IPipelineInterface> pPipelineInterface_;

    std::shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    void createStage(EPipelineStageId stageId, EPipelineQueueType queueId);
};
}  // namespace sc

#endif
