#ifndef SEAMCARVERPROCESSORFACTORY_HPP
#define SEAMCARVERPROCESSORFACTORY_HPP

#include <memory>
#include <unordered_map>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class SeamCarverProcessorFactory
{
  public:
    typedef std::shared_ptr<ISeamCarverDataProcessor> (*createProcessorFunction)();

    static SeamCarverProcessorFactory& getFactoryInstance();

    void registerNewStage(EPipelineStageId stageId, createProcessorFunction function);

    std::shared_ptr<ISeamCarverDataProcessor> createStage(EPipelineStageId stageId);

    // deleted to prevent misuse
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&&) = delete;

  private:
    SeamCarverProcessorFactory() = default;

    ~SeamCarverProcessorFactory() = default;

    std::unordered_map<EPipelineStageId, createProcessorFunction> stageIdToCreateProcessorFunctionMap_;
};
}  // namespace sc

#endif
