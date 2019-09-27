#pragma once

namespace sc
{
class IPipelineStage
{
  public:
    virtual ~IPipelineStage() = default;

    virtual void runComponent() = 0;

    virtual void stopComponent() = 0;

    virtual bool isComponentRunning() const noexcept = 0;
};

}  // namespace sc
