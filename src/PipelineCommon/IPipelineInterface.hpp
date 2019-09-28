#pragma once

#include <memory>

#include "PipelineDataBase.hpp"

namespace pipeline
{
class IPipelineInterface
{
  public:
    virtual ~IPipelineInterface() = 0;

    virtual void addNewDataToPipeline(std::unique_ptr<PipelineDataBase>& pPipelineData) = 0;

    virtual std::unique_ptr<PipelineDataBase> getOutputFromPipeline() = 0;

    virtual bool doesNewResultExist() const = 0;

    virtual size_t getNumberOfDataObjectsInPipeline() const = 0;
};

}  // namespace pipeline
