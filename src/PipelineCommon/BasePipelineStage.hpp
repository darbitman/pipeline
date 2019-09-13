#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"

namespace sc
{
class BasePipelineStage : public IPipelineStage
{
  public:
    explicit BasePipelineStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                               PipelineSenderReceiver* pSenderReceiver);

    /// @brief Destructor will stop the thread if it needs to be stopped, and 'uninitialize'
    virtual ~BasePipelineStage() override;

    /// @brief This method initializes this stage so that it's ready to be started. This call will
    /// fail if the constructor was passed a nullptr for pSenderReceiver.
    virtual void initialize() override;

    /// @brief This method start the thread that will read the input queue and process the message
    /// and the data contained in the message. This call will not start the thread if this
    /// BasePipelineStage was not initialized.
    virtual void runStage() override;

    /// @brief This method stops the thread that reads the input queue
    virtual void stopStage() override;

    /// @brief Returns the status of this stage
    /// @return bool
    virtual bool isInitialized() const override;

    /// @brief Returns the status of the thread
    /// @return bool
    virtual bool isRunning() const override;

    // deleted to prevent misuse
    BasePipelineStage(const BasePipelineStage&) = delete;
    BasePipelineStage(BasePipelineStage&&) = delete;
    BasePipelineStage& operator=(const BasePipelineStage&) = delete;
    BasePipelineStage& operator=(BasePipelineStage&&) = delete;

  protected:
    /// @brief method that processes the incoming message
    /// @param pMessage
    virtual void processMessage(std::unique_ptr<BasePipelineMessage>& pMessage) = 0;

    /// @brief method that does the actual data processing
    /// @param pData
    virtual void processData(std::unique_ptr<BasePipelineData>& pData) = 0;

  private:
    void runThread();

    void doStopStage();

    const EPipelineStageId thisStageId_;

    const EPipelineQueueType queueType_;

    /// Flag to start and stop the thread, and to keep track if it's running
    std::atomic<bool> bThreadIsRunning_;

    /// Indicates if this stage is initialized
    bool bIsInitialized_;

    /// Inidicates whether the thread has joined
    bool bThreadHasJoined_;

    /// pointer to a PipelineSenderReceiver
    /// This BasePipelineStage does not own this pointer so not responsible for deleting
    PipelineSenderReceiver* pSenderReceiver_;

    std::thread processingThread_;
};

}  // namespace sc
