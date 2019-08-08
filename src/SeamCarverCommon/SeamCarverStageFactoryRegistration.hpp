#ifndef SEAMCARVERSTAGEFACTORYREGISTRATION_HPP
#define SEAMCARVERSTAGEFACTORYREGISTRATION_HPP

#include <cstdint>

#include "PipelineCommon.hpp"
#include "SeamCarverStageFactory.hpp"

namespace sc
{
class SeamCarverStageFactoryRegistration
{
  public:
    SeamCarverStageFactoryRegistration(EPipelineStageId pipelineStageId,
                                       SeamCarverStageFactory::createStageFunction function);

    SeamCarverStageFactoryRegistration(const SeamCarverStageFactoryRegistration&) = delete;
    SeamCarverStageFactoryRegistration(const SeamCarverStageFactoryRegistration&&) = delete;
    SeamCarverStageFactoryRegistration& operator=(const SeamCarverStageFactoryRegistration&) =
        delete;
    SeamCarverStageFactoryRegistration& operator=(const SeamCarverStageFactoryRegistration&&) =
        delete;
};
}  // namespace sc

#endif
