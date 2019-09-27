#pragma once

#include <memory>

namespace sc
{
class BasePipelineMessage;
class BasePipelineData;

class IDataProcessor
{
  public:
    ~IDataProcessor() = default;

    virtual void processMessage(std::unique_ptr<BasePipelineMessage>& pMessage) = 0;

  protected:
    virtual void processData(BasePipelineData* pData) = 0;
};

}  // namespace sc
