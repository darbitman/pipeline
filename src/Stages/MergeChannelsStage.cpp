#include "MergeChannelsStage.hpp"

#include <memory>
#include <thread>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SeamCarverStageFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace sc
{
MergeChannelsStage::MergeChannelsStage(shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : BasePipelineStage(EPipelineStageId::STAGE_4, EPipelineQueueType::QUEUE_TYPE_FIFO,
                        pSenderReceiver)
{
}

MergeChannelsStage::~MergeChannelsStage() {}

void MergeChannelsStage::initialize() { BasePipelineStage::initialize(); }

void MergeChannelsStage::runStage() { BasePipelineStage::runStage(); }

void MergeChannelsStage::stopStage() { BasePipelineStage::stopStage(); }

bool MergeChannelsStage::isInitialized() const { return BasePipelineStage::isInitialized(); }

bool MergeChannelsStage::isRunning() const { return BasePipelineStage::isRunning(); }

void MergeChannelsStage::processData(shared_ptr<BasePipelineData> pData)
{
    auto pSeamCarverData = (VerticalSeamCarverData*)(pData.get());
}

// void MergeChannelsStage::mergeChannels(VerticalSeamCarverData* data)
// {
//     merge(data->bgr, *(data->getSavedImage()));
// }

namespace
{
SeamCarverStageFactoryRegistration registerstage(
    EPipelineStageId::STAGE_4, [](shared_ptr<PipelineSenderReceiver> pSenderReceiver) {
        return dynamic_pointer_cast<IPipelineStage>(
            make_shared<MergeChannelsStage>(pSenderReceiver));
    });
}

}  // namespace sc
