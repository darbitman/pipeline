#include "PipelineMessageRouter.hpp"

#include <memory>
#include <thread>

#include "PipelineSenderReceiver.hpp"

using std::shared_ptr;
using std::thread;

namespace sc
{
PipelineMessageRouter::PipelineMessageRouter(shared_ptr<PipelineSenderReceiver> pSenderReceiver,
                                             int32_t thisStage)
    : bInitialized_(false),
      thisStage_(thisStage),
      bRunReceiverThread_(false),
      bReceiverThreadShutdown_(true),
      pSenderReceiver_(pSenderReceiver)
{
}

PipelineMessageRouter::~PipelineMessageRouter() {}

void PipelineMessageRouter::initialize()
{
    if (!bInitialized_ && pSenderReceiver_ != nullptr)
    {
        thread(&PipelineMessageRouter::receiverThread, this).detach();

        bInitialized_ = true;
    }
}

void PipelineMessageRouter::receiverThread()
{
    bRunReceiverThread_ = true;
    bReceiverThreadShutdown_ = false;

    while (bRunReceiverThread_)
    {
        if (pSenderReceiver_ != nullptr) {
            auto pReceivedMessage = pSenderReceiver_->receive(thisStage_);

            if (pReceivedMessage != nullptr) {
                pReceivedMessage->
            }
        }
        // check if valid
        // check for message (and forward)
        // OR check for a stage register message (and register)
        // OR check for stage unregister message (and unregister)
        // OR check for shutdown message (and shutdown thread)
    }
}
}  // namespace sc