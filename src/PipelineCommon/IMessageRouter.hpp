#pragma once

#include <cstdint>
#include <memory>

namespace pipeline
{
class PipelineMessageBase;

class IMessageRouter
{
  public:
    virtual ~IMessageRouter() = default;

    virtual void registerComponent(uint32_t componentId, uint32_t componentLinkType) noexcept = 0;

    virtual void unregisterComponent(uint32_t componentId) noexcept = 0;

    virtual bool isComponentRegistered(uint32_t componentId) const noexcept = 0;

    virtual void sendMessage(std::unique_ptr<PipelineMessageBase>& pMessage) noexcept = 0;

    virtual void sendMessage(std::unique_ptr<PipelineMessageBase>&& pMessage) noexcept = 0;

    virtual std::unique_ptr<PipelineMessageBase> receiveMessage(
        uint32_t receivingComponentId) noexcept = 0;

    virtual bool canReceive(uint32_t receivingComponentId) const noexcept = 0;
};

}  // namespace pipeline
