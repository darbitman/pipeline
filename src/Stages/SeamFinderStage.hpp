#ifndef SEAMFINDERSTAGE_HPP
#define SEAMFINDERSTAGE_HPP

#include <memory>

#include "BasePipelineStage.hpp"
#include "PipelineSenderReceiver.hpp"

namespace sc
{
class VerticalSeamCarverData;

class SeamFinderStage : public BasePipelineStage
{
  public:
    explicit SeamFinderStage(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~SeamFinderStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    SeamFinderStage(const SeamFinderStage&) = delete;
    SeamFinderStage(SeamFinderStage&&) = delete;
    SeamFinderStage& operator=(const SeamFinderStage&) = delete;
    SeamFinderStage& operator=(SeamFinderStage&&) = delete;

  protected:
    /**
     * @brief method that does the actual data processing
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData) override;

  private:
    // void findSeams(VerticalSeamCarverData* data);
};
}  // namespace sc

#endif