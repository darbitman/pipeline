#pragma once

#include <memory>

namespace pipeline
{
class PipelineDataBase;

class IDataProcessor
{
  public:
    ~IDataProcessor() = default;

    /// @brief This is the callback method to be invoked to process the data
    /// @param pData Reference to the data object
    virtual void processData(PipelineDataBase* pData) = 0;
};

}  // namespace pipeline
