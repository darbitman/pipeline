#pragma once

#include <cstdint>
#include <memory>

#include "PipelineCommon.hpp"

namespace sc
{
class BasePipelineMessage;

class IMessageRouter
{
  public:
    virtual ~IMessageRouter() = default;

    virtual void registerComponent(EComponentId componentId,
                                   EComponentLinkType componentLinkType) noexcept = 0;

    virtual void unregisterComponent(EComponentId componentId) noexcept = 0;

    virtual bool isComponentRegistered(EComponentId componentId) const noexcept = 0;

    virtual void sendMessage(std::unique_ptr<BasePipelineMessage>& pMessage) noexcept = 0;

    virtual void sendMessage(std::unique_ptr<BasePipelineMessage>&& pMessage) noexcept = 0;

    virtual std::unique_ptr<BasePipelineMessage> receiveMessage(
        EComponentId receivingComponentId) noexcept = 0;

    virtual bool canReceive(EComponentId receivingComponentId) const noexcept = 0;
};

}  // namespace sc
