#ifndef IPIPELINEINTERFACE_HPP
#define IPIPELINEINTERFACE_HPP

#include <memory>

#include "BasePipelineData.hpp"

namespace sc
{
class IPipelineInterface
{
  public:
    virtual ~IPipelineInterface() = 0;

    virtual void addNewDataToPipeline(std::shared_ptr<BasePipelineData> pPipelineData) = 0;

    virtual std::shared_ptr<BasePipelineData> getOutputFromPipeline() = 0;

    virtual bool doesNewResultExist() const = 0;

    virtual size_t getNumberOfDataObjectsInPipeline() const = 0;
};

}  // namespace sc

#endif