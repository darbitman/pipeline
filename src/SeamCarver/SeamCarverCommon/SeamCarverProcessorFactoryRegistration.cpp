#include "SeamCarverProcessorFactoryRegistration.hpp"

#include "PipelineCommon.hpp"
#include "SeamCarverProcessorFactory.hpp"

namespace sc
{
SeamCarverProcessorFactoryRegistration::SeamCarverProcessorFactoryRegistration(
    EPipelineStageId pipelineStageId, SeamCarverProcessorFactory::createProcessorFunction function)
{
    SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(pipelineStageId, function);
}
}  // namespace sc
