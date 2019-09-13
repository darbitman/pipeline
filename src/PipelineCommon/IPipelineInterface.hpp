#pragma once

#include <memory>

#include "BasePipelineData.hpp"

namespace sc
{
class IPipelineInterface
{
  public:
    virtual ~IPipelineInterface() = 0;

    virtual void addNewDataToPipeline(std::unique_ptr<BasePipelineData>& pPipelineData) = 0;

    virtual std::unique_ptr<BasePipelineData> getOutputFromPipeline() = 0;

    virtual bool doesNewResultExist() const = 0;

    virtual size_t getNumberOfDataObjectsInPipeline() const = 0;
};

}  // namespace sc
