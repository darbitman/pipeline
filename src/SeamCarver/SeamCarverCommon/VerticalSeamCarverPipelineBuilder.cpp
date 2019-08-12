#include "VerticalSeamCarverPipelineBuilder.hpp"

#include <memory>
#include <vector>

#include "BaseSeamCarverInterface.hpp"
#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"
#include "SeamCarverProcessorFactory.hpp"

using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace sc
{
VerticalSeamCarverPipelineBuilder::VerticalSeamCarverPipelineBuilder(
    shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : pSenderReceiver_(pSenderReceiver)
{
}

VerticalSeamCarverPipelineBuilder::~VerticalSeamCarverPipelineBuilder() {}

shared_ptr<vector<vector<shared_ptr<IPipelineStage>>>>
VerticalSeamCarverPipelineBuilder::createPipeline()
{
    if (pPipelineInterface_ == nullptr)
    {
        pPipelineStages_ = make_shared<vector<vector<shared_ptr<IPipelineStage>>>>();
        // TODO
    }

    return pPipelineStages_;
}

shared_ptr<IPipelineInterface> VerticalSeamCarverPipelineBuilder::createPipelineInterface()
{
    if (pPipelineInterface_ == nullptr)
    {
        pPipelineInterface_ = make_shared<BaseSeamCarverInterface>(
            EPipelineQueueType::QUEUE_TYPE_FIFO, pSenderReceiver_);
    }

    return pPipelineInterface_;
}

}  // namespace sc
