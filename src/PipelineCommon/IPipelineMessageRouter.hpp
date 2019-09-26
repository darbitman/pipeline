#pragma once

#include <cstdint>

namespace sc
{
enum EComponentId : uint32_t;
enum E : uint32_t;

class IPipelineMessageRouter
{
  public:
    virtual void initialize() = 0;

    virtual void registerNewComponent(EPipelineStageId componentId, EPipelineQueueType queueType) = 0;

    virtual void unregisterComponent(EPipelineStageId stageId) = 0;

    virtual void isComponentRegistered(EPipelineStageId stageId) = 0;
};

}  // namespace sc
