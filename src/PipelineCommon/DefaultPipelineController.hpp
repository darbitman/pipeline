#pragma once

namespace pipeline
{
class IPipelineBuilder;

class DefaultPipelineController
{
  public:
    explicit DefaultPipelineController(IPipelineBuilder* pPipelineBuilder) noexcept;

    virtual ~DefaultPipelineController() = default;

    virtual void runAllComponents() noexcept;

    virtual void stopAllComponents() noexcept;
};

}  // namespace pipeline