#pragma once

#include <memory>

namespace pipeline
{
class PipelineMessageBase;
class BasePipelineData;

class IDataProcessor
{
  public:
    ~IDataProcessor() = default;

    virtual void processMessage(std::unique_ptr<PipelineMessageBase>& pMessage) = 0;

  protected:
    virtual void processData(BasePipelineData* pData) = 0;
};

}  // namespace pipeline
