#pragma once

namespace pipeline
{
class IPipelineStage
{
  public:
    virtual ~IPipelineStage() = default;

    virtual void runComponent() = 0;

    virtual void stopComponent() = 0;

    virtual bool isComponentRunning() const noexcept = 0;
};

}  // namespace pipeline
