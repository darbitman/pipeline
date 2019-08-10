#include "SeamCarverPipelineBuilder.hpp"

#include <memory>
#include <vector>

#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"
#include "SeamCarverProcessorFactory.hpp"

using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace sc
{
SeamCarverPipelineBuilder::SeamCarverPipelineBuilder() {}

SeamCarverPipelineBuilder::~SeamCarverPipelineBuilder() {}

shared_ptr<vector<shared_ptr<IPipelineStage>>> SeamCarverPipelineBuilder::buildPipeline()
{
    // TODO

    return nullptr;
}

}  // namespace sc
