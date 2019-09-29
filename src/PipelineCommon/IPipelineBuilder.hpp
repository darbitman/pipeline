#pragma once

#include <memory>

namespace pipeline
{
class IDataProcessor;

class IPipelineBuilder
{
  public:
    virtual ~IPipelineBuilder() = default;

    virtual void addNewDataProcessor(std::unique_ptr<IDataProcessor> pDataProcessor,
                                     uint32_t componentNumber) = 0;
};

}  // namespace pipeline
