#ifndef COMPUTEENERGYSTAGE_HPP
#define COMPUTEENERGYSTAGE_HPP

#include <memory>

#include "BasePipelineStage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SeamCarverStageFactory.hpp"

namespace sc
{
class ComputeEnergyStage : public BasePipelineStage
{
  public:
    explicit ComputeEnergyStage(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver);

    virtual ~ComputeEnergyStage();

    virtual void initialize() override;

    virtual void runStage() override;

    virtual void stopStage() override;

    virtual bool isInitialized() const override;

    virtual bool isRunning() const override;

    // deleted to prevent misuse
    ComputeEnergyStage(const ComputeEnergyStage&) = delete;
    ComputeEnergyStage(ComputeEnergyStage&&) = delete;
    ComputeEnergyStage& operator=(const ComputeEnergyStage&) = delete;
    ComputeEnergyStage& operator=(ComputeEnergyStage&&) = delete;

  protected:
    /**
     * @brief method that does the actual data processing
     */
    virtual void processData(std::shared_ptr<BasePipelineData> pData) override;

  private:
    // // image dimensions
    // size_t numRows_;
    // size_t numColumns_;
    // size_t bottomRow_;
    // size_t rightColumn_;
    // size_t numColorChannels_;
    // double marginEnergy_;

    // void calculatePixelEnergy(const std::shared_ptr<const cv::Mat>& image,
    //                           std::vector<std::vector<double>>& outPixelEnergy);

    // void calculatePixelEnergyForEveryRow(const std::shared_ptr<const cv::Mat>& image,
    //                                      std::vector<std::vector<double>>& outPixelEnergy,
    //                                      bool bDoOddColumns);

    // void calculatePixelEnergyForEveryColumn(const std::shared_ptr<const cv::Mat>& image,
    //                                         std::vector<std::vector<double>>& outPixelEnergy,
    //                                         bool bDoOddRows);

    inline static const bool bRegistered_ =
        SeamCarverStageFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_0, [](std::shared_ptr<PipelineSenderReceiver> pSenderReceiver) {
                return std::dynamic_pointer_cast<IPipelineStage>(
                    std::make_shared<ComputeEnergyStage>(pSenderReceiver));
            });
};
}  // namespace sc

#endif
