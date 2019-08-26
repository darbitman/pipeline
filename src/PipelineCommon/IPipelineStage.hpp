#ifndef IPIPELINESTAGE_HPP
#define IPIPELINESTAGE_HPP

#include <memory>

#include "PipelineSenderReceiver.hpp"

namespace sc
{
class IPipelineStage
{
  public:
    virtual ~IPipelineStage() = default;

    virtual void initialize() = 0;

    virtual void runStage() = 0;

    virtual void stopStage() = 0;

    virtual bool isInitialized() const = 0;

    virtual bool isRunning() const = 0;
};
}  // namespace sc

#endif
