#ifndef SEAMCARVERPROCESSORFACTORY_HPP
#define SEAMCARVERPROCESSORFACTORY_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include "ISeamCarverDataProcessor.hpp"
#include "PipelineIdentifiers.hpp"

namespace sc
{
class SeamCarverProcessorFactory
{
  public:
    using createProcessorFunction = std::unique_ptr<ISeamCarverDataProcessor> (*)();

    static bool registerComponent(uint32_t stageId, createProcessorFunction function);

    static bool isComponentRegistered(uint32_t stageId);

    static std::unique_ptr<ISeamCarverDataProcessor> createStage(uint32_t stageId);

    static std::unique_ptr<std::vector<uint32_t>> getVectorOfRegisteredStages();

    // deleted to prevent misuse
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory(const SeamCarverProcessorFactory&&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&) = delete;
    SeamCarverProcessorFactory& operator=(const SeamCarverProcessorFactory&&) = delete;

  private:
    SeamCarverProcessorFactory() = default;

    ~SeamCarverProcessorFactory() = default;

    inline static std::unordered_map<uint32_t, createProcessorFunction>
        stageIdToCreateProcessorFunctionMap_;
};
}  // namespace sc

#endif
