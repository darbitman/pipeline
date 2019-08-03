#ifndef BASEPIPELINESTAGE_HPP
#define BASEPIPELINESTAGE_HPP

#include <atomic>
#include <memory>
#include <mutex>

#include "IPipelineStage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "StageNumbers.hpp"

namespace sc
{
class BasePipelineStage : public IPipelineStage
{
  public:
    explicit BasePipelineStage(
        int32_t thisStageNumber,
        std::shared_ptr<PipelineSenderReceiver> pSenderRcvr);

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
    virtual void processData(BasePipelineData* data);

  private:
    const int32_t thisStageNumber_;

    /// Flag to start and stop the thread, and to keep track if it's running
    std::atomic<bool> bThreadIsRunning_;

    // Indicates if this stage is initialized
    bool bIsInitialized_;

    /// initialized in the initialize() call
    std::shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    void runThread();

    void doStopStage();

    int32_t getPipelineStageNumber() const;
};
}  // namespace sc

#endif
