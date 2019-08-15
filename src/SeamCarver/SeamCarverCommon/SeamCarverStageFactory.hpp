#ifndef SEAMCARVERSTAGEFACTORY_HPP
#define SEAMCARVERSTAGEFACTORY_HPP

#include <memory>
#include <unordered_map>

#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"

namespace sc
{
class SeamCarverStageFactory
{
  public:
    typedef std::shared_ptr<IPipelineStage> (*createStageFunction)(
        std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    static SeamCarverStageFactory& getFactoryInstance();

    virtual bool registerNewStage(uint32_t stageId, createStageFunction function);

    virtual std::shared_ptr<IPipelineStage> createStage(
        EPipelineStageId stageId, std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    // deleted to prevent misuse
    SeamCarverStageFactory(const SeamCarverStageFactory&) = delete;
    SeamCarverStageFactory(const SeamCarverStageFactory&&) = delete;
    SeamCarverStageFactory& operator=(const SeamCarverStageFactory&) = delete;
    SeamCarverStageFactory& operator=(const SeamCarverStageFactory&&) = delete;

  private:
    SeamCarverStageFactory() = default;

    ~SeamCarverStageFactory() = default;

    std::unordered_map<uint32_t, createStageFunction> stage_id_to_createstagefunc_map_;
};
}  // namespace sc

#endif
