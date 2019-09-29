#pragma once

#include <memory>

#include "PipelineDataBase.hpp"

namespace pipeline
{
class IPipelineInterface
{
  public:
    virtual ~IPipelineInterface() = default;

    /// @brief This injects/sends data into the pipeline
    /// @param pPipelineData Since this is passed by reference, when this method completes
    /// successfuly, the original pointer will be set to nullptr. (ie ownership is transferred)
    virtual void addNewDataToPipeline(std::unique_ptr<PipelineDataBase>& pPipelineData) const
        noexcept = 0;

    /// @brief Retrieve a result from the pipeline
    /// @return std::unique_ptr<PipelineDataBase> If no data available, a nullptr is returned
    virtual std::unique_ptr<PipelineDataBase> getOutputFromPipeline() const noexcept = 0;

    /// @brief Checks whether a result is available
    /// @return bool Returns true if a result is available to be received from the pipeline
    virtual bool doesNewResultExist() const noexcept = 0;

    virtual size_t getNumberOfDataObjectsInPipeline() const noexcept = 0;
};

}  // namespace pipeline
