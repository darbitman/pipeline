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
    typedef std::unique_ptr<IPipelineStage> (*createStageFunction)(
        PipelineSenderReceiver* pSenderReceiver);

    static SeamCarverStageFactory& getFactoryInstance();

    virtual bool registerNewStage(uint32_t stageId, createStageFunction function);

    virtual std::unique_ptr<IPipelineStage> createStage(EPipelineStageId stageId,
                                                        PipelineSenderReceiver* pSenderReceiver);

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
