#ifndef BASEPIPELINESTAGE_HPP
#define BASEPIPELINESTAGE_HPP

#include <atomic>
#include <memory>
#include <mutex>

#include "IPipelineStage.hpp"
#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"

namespace sc
{
class BasePipelineStage : public IPipelineStage
{
  public:
    explicit BasePipelineStage(EPipelineStageId thisStageId, EPipelineQueueType queueType,
                               std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~BasePipelineStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    BasePipelineStage(const BasePipelineStage&) = delete;
    BasePipelineStage(BasePipelineStage&&) = delete;
    BasePipelineStage& operator=(const BasePipelineStage&) = delete;
    BasePipelineStage& operator=(BasePipelineStage&&) = delete;

  protected:
    /**
     * @brief method that does the actual data processing
     * derived class MUST provide an implementation
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData);

    virtual void processMessage(std::shared_ptr<BasePipelineMessage> pMessage);

  private:
    const EPipelineStageId thisStageId_;

    const EPipelineQueueType queueType_;

    /// Flag to start and stop the thread, and to keep track if it's running
    std::atomic<bool> bThreadIsRunning_;

    // Indicates if this stage is initialized
    bool bIsInitialized_;

    std::shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    void runThread();

    void doStopStage();
};
}  // namespace sc

#endif
