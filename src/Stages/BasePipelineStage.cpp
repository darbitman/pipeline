#include "BasePipelineStage.hpp"

#include <thread>

#include "BasePipelineData.hpp"

using std::shared_ptr;
using std::thread;
using std::unique_lock;

namespace sc
{
BasePipelineStage::BasePipelineStage(
    int32_t thisStageNumber, shared_ptr<PipelineSenderReceiver> pSenderRcvr)
    : thisStageNumber_(thisStageNumber),
      bThreadIsRunning_(false),
      bIsInitialized_(false)
{
}

BasePipelineStage::~BasePipelineStage()
{
    // TODO IMPLEMENT
}

void BasePipelineStage::initialize()
{
    if (bIsInitialized_ == false && pSenderReceiver_ != nullptr)
    {
        bIsInitialized_ = true;
    }
}

void BasePipelineStage::runStage()
{
    if (bIsInitialized_ && !bThreadIsRunning_)
    {
        bThreadIsRunning_ = true;
        thread(&BasePipelineStage::runThread, this).detach();
    }
}

void BasePipelineStage::stopStage() { doStopStage(); }

bool BasePipelineStage::isInitialized() const { return bIsInitialized_; }

bool BasePipelineStage::isRunning() const { return bThreadIsRunning_; }

void BasePipelineStage::runThread()
{
    while (bThreadIsRunning_)
    {
        BasePipelineData* pData =
            pSenderReceiver_->receive(getPipelineStageNumber());

        if (pData != nullptr)
        {
            // check if message is a shutdown message
            if (pData->GetShutdownFlag())
            {
                delete pData;
                break;
            }
            else
            {
                processData(pData);

                // forward result to the next stage
                pSenderReceiver_->sendTo(getPipelineStageNumber() + 1, pData);
            }
        }
    }

    bThreadIsRunning_ = false;
}

void BasePipelineStage::doStopStage()
{
    // send a shutdown message to itself
    VerticalSeamCarverData* pData = new VerticalSeamCarverData();
    pData->SetShutdownFlag();

    // TODO IMPLEMENT
    // pSenderReceiver_->sendTo(pData);
}

void BasePipelineStage::processData(BasePipelineData* pData)
{
    // DEFINE IN DERIVED CLASS
}

int32_t BasePipelineStage::getPipelineStageNumber() const
{
    return thisStageNumber_;
}
}  // namespace sc