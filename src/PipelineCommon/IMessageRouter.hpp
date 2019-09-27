#pragma once

#include <cstdint>

#include "PipelineCommon.hpp"

namespace sc
{
class IPipelineMessageRouter
{
  public:
    virtual void initialize() = 0;

    virtual void registerNewComponent(EComponentId componentId, EComponentLinkType queueType) = 0;

    virtual void unregisterComponent(EComponentId componentId) = 0;

    virtual void isComponentRegistered(EComponentId componentId) = 0;
};

}  // namespace sc
