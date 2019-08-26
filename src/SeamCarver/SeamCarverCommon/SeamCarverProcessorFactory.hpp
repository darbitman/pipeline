#ifndef SEAMCARVERPROCESSORFACTORY_HPP
#define SEAMCARVERPROCESSORFACTORY_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class SeamCarverProcessorFactory
{
  public:
    using createProcessorFunction = std::unique_ptr<ISeamCarverDataProcessor> (*)();

    static bool registerNewStage(EPipelineStageId stageId, createProcessorFunction function);

    static bool isStageRegistered(EPipelineStageId stageId);

    static std::unique_ptr<ISeamCarverDataProcessor> createStage(EPipelineStageId stageId);

    static std::unique_ptr<std::vector<EPipelineStageId>> getVectorOfRegisteredStages();

    // deleted to prevent misuse
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&&) = delete;

  private:
    SeamCarverProcessorFactory() = default;

    ~SeamCarverProcessorFactory() = default;

    inline static std::unordered_map<EPipelineStageId, createProcessorFunction>
        stageIdToCreateProcessorFunctionMap_;
};
}  // namespace sc

#endif
