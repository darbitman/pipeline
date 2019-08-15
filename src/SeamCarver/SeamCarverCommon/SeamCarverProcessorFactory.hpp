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
    typedef std::shared_ptr<ISeamCarverDataProcessor> (*createProcessorFunction)();

    static SeamCarverProcessorFactory& getFactoryInstance();

    virtual bool registerNewStage(EPipelineStageId stageId, createProcessorFunction function);

    virtual bool isStageRegistered(EPipelineStageId stageId) const;

    std::shared_ptr<ISeamCarverDataProcessor> createStage(EPipelineStageId stageId);

    std::shared_ptr<std::vector<EPipelineStageId>> getVectorOfRegisteredStages() const;

    // deleted to prevent misuse
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&&) = delete;

  private:
    SeamCarverProcessorFactory() = default;

    ~SeamCarverProcessorFactory() = default;

    std::unordered_map<EPipelineStageId, createProcessorFunction>
        stageIdToCreateProcessorFunctionMap_;
};
}  // namespace sc

#endif
