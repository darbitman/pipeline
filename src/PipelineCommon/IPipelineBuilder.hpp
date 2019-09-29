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
    /// @param pDataProcessor A reference to the IDataProcessor implementation. This will transfer
    /// ownership of the pointer.
    /// @param stageNumber
    virtual void addNewDataProcessor(std::unique_ptr<IDataProcessor>& pDataProcessor,
                                     uint32_t stageNumber) = 0;
};

}  // namespace pipeline
