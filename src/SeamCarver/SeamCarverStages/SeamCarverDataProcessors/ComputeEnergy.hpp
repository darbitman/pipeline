#pragma once

#include <memory>
#include <opencv2/opencv.hpp>
#include <vector>

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class ComputeEnergy : public ISeamCarverDataProcessor
{
  public:
    ComputeEnergy() = default;

    virtual ~ComputeEnergy() override = default;

    virtual void runSeamCarverProcessor(BasePipelineData* pData) override;

    // deleted to prevent misuse
    ComputeEnergy(const ComputeEnergy&) = delete;
    ComputeEnergy(ComputeEnergy&&) = delete;
    ComputeEnergy& operator=(const ComputeEnergy&) = delete;
    ComputeEnergy& operator=(ComputeEnergy&&) = delete;

  private:
    void calculatePixelEnergy(const std::unique_ptr<const cv::Mat>& image,
                              std::vector<std::vector<double>>& outPixelEnergy);

    void calculatePixelEnergyForEveryRow(const std::unique_ptr<const cv::Mat>& image,
                                         std::vector<std::vector<double>>& outPixelEnergy,
                                         bool bDoOddColumns);

    void calculatePixelEnergyForEveryColumn(const std::unique_ptr<const cv::Mat>& image,
                                            std::vector<std::vector<double>>& outPixelEnergy,
                                            bool bDoOddRows);

    // image dimensions
    size_t numRows_;
    size_t numColumns_;
    size_t bottomRow_;
    size_t rightColumn_;
    size_t numColorChannels_;
    double marginEnergy_;

    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::registerNewStage(EPipelineStageId::STAGE_0, []() {
            std::unique_ptr<ISeamCarverDataProcessor> pNewSeamCarverDataProcessor =
                std::make_unique<ComputeEnergy>();

            return pNewSeamCarverDataProcessor;
        });
};

}  // namespace sc
