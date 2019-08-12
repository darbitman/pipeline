#include "VerticalSeamCarverPipelineBuilder.hpp"

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
VerticalSeamCarverPipelineBuilder::VerticalSeamCarverPipelineBuilder()
    : bPipelineStagesCreated_(false)
{
}

VerticalSeamCarverPipelineBuilder::~VerticalSeamCarverPipelineBuilder() {}

shared_ptr<vector<vector<shared_ptr<IPipelineStage>>>>
VerticalSeamCarverPipelineBuilder::createPipeline()
{
    if (!bPipelineStagesCreated_)
    {
        pPipelineStages_ = make_shared<vector<vector<shared_ptr<IPipelineStage>>>>();
        // TODO
        bPipelineStagesCreated_ = true;
    }

    return pPipelineStages_;
}

shared_ptr<IPipelineInterface> VerticalSeamCarverPipelineBuilder::createPipelineInterface()
{
    // TODO
    return nullptr;
}

}  // namespace sc
