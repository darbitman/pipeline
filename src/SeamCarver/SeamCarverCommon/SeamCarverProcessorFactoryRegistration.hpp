#ifndef SEAMCARVERPROCESSORFACTORYREGISTRATION_HPP
#define SEAMCARVERPROCESSORFACTORYREGISTRATION_HPP

#include <cstdint>

#include "PipelineCommon.hpp"
#include "SeamCarverProcessorFactory.hpp"

namespace sc
{
class SeamCarverProcessorFactoryRegistration
{
  public:
    SeamCarverProcessorFactoryRegistration(
        EPipelineStageId pipelineStageId,
        SeamCarverProcessorFactory::createProcessorFunction function);

    // deleted to prevent misuse
    SeamCarverProcessorFactoryRegistration(const SeamCarverProcessorFactoryRegistration&) = delete;
    SeamCarverProcessorFactoryRegistration(const SeamCarverProcessorFactoryRegistration&&) = delete;
    SeamCarverProcessorFactoryRegistration& operator=(
        const SeamCarverProcessorFactoryRegistration&) = delete;
    SeamCarverProcessorFactoryRegistration& operator=(
        const SeamCarverProcessorFactoryRegistration&&) = delete;
};

}  // namespace sc

#endif
