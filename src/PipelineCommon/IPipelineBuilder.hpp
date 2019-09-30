#pragma once

#include <memory>

namespace pipeline
{
class IDataProcessor;

class IPipelineBuilder
{
  public:
    virtual ~IPipelineBuilder() = default;

    /// @brief adds a new data processor object for a specific stage in the pipeline
    /// @param stageNumber The identifier for the component to add
    virtual void addNewComponent(uint32_t stageNumber) noexcept = 0;
};

}  // namespace pipeline
