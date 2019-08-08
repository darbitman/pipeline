#include "SeamCarverStageFactoryRegistration.hpp"

#include <cstdint>

#include "PipelineCommon.hpp"
#include "SeamCarverStageFactory.hpp"

namespace sc
{
SeamCarverStageFactoryRegistration::SeamCarverStageFactoryRegistration(
    EPipelineStageId pipelineStageId, SeamCarverStageFactory::createStageFunction function)
{
    SeamCarverStageFactory::getFactoryInstance().registerNewStage(pipelineStageId, function);
}
}  // namespace sc
