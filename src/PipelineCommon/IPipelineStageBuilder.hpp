#ifndef IPIPELINESTAGEBUILDER_HPP
#define IPIPELINESTAGEBUILDER_HPP

#include <memory>
#include <vector>

#include "IPipelineStage.hpp"

namespace sc
{
class IPipelineStageBuilder
{
  public:
    virtual ~IPipelineStageBuilder();

    virtual std::shared_ptr<std::vector<std::shared_ptr<IPipelineStage>>> buildPipeline() = 0;

    
};

}  // namespace sc

#endif
