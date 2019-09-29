#pragma once

#include <memory>

namespace pipeline
{
class PipelineMessageBase;

class IDataProcessor
{
  public:
    ~IDataProcessor() = default;

    /// @brief This is the callback method to be invoked once a message is received.
    /// @param pMessage This is the 'envelope' that holds the data to process.
    /// It is up to the client to update the source and destination of this message once processing
    /// on the data is done.
    virtual void processMessage(std::unique_ptr<PipelineMessageBase>& pMessage) = 0;
};

}  // namespace pipeline
