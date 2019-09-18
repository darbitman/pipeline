#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "IPipelineStage.hpp"
#include "IPipelineStageBuilder.hpp"
#include "PipelineSenderReceiver.hpp"

namespace sc
{
class IPipelineInterface;
class VerticalSeamCarverPipelineBuilder : public IPipelineStageBuilder
{
  public:
    explicit VerticalSeamCarverPipelineBuilder(PipelineSenderReceiver* pSenderReceiver);

    virtual ~VerticalSeamCarverPipelineBuilder() = default;

    /// @brief Creates the default pipeline stages
    virtual void createPipeline() override;

    /// @brief creates an additional stage
    /// @param stageId
    /// @param queueType
    /// @return std::unique_ptr<IPipelineStage>
    virtual std::unique_ptr<IPipelineStage> createNewStage(EPipelineStageId stageId,
                                                           EPipelineQueueType queueType) override;

    /// @brief Creates the interface stage which feeds data into the pipeline
    /// @param std::unique_ptr<IPipelineInterface>&
    virtual std::unique_ptr<IPipelineInterface>& createPipelineInterface() override;

    /// @brief Retrieves stages (can return parallel stages)
    /// @param stageId
    /// @return std::vector<std::unique_ptr<IPipelineStage>>* If stage doesn't exist, nullptr will
    /// be returned
    virtual std::vector<std::unique_ptr<IPipelineStage>>* getStages(
        EPipelineStageId stageId) const override;

  private:
    bool bPipelineCreated_;

    std::unordered_map<EPipelineStageId,
                       std::unique_ptr<std::vector<std::unique_ptr<IPipelineStage>>>>
        stageIdToVectorOfPipelineStages_;

    std::unique_ptr<IPipelineInterface> pPipelineInterface_;

    PipelineSenderReceiver* pSenderReceiver_;

    void createStage(EPipelineStageId stageId, EPipelineQueueType queueType);
};

}  // namespace sc
