#ifndef COMPUTEENERGY_HPP
#define COMPUTEENERGY_HPP

#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

#include "ISeamCarverDataProcessor.hpp"
#include "SeamCarverProcessorFactory.hpp"
#include "VerticalSeamCarverData.hpp"

namespace sc
{
class ComputeEnergy : public ISeamCarverDataProcessor
{
  public:
    ComputeEnergy();

    virtual ~ComputeEnergy();

    virtual void runSeamCarverProcessor(std::shared_ptr<VerticalSeamCarverData> pData) override;

    // deleted to prevent misuse
    ComputeEnergy(const ComputeEnergy&) = delete;
    ComputeEnergy(ComputeEnergy&&) = delete;
    ComputeEnergy& operator=(const ComputeEnergy&) = delete;
    ComputeEnergy& operator=(ComputeEnergy&&) = delete;

  private:
    // image dimensions
    size_t numRows_;
    size_t numColumns_;
    size_t bottomRow_;
    size_t rightColumn_;
    size_t numColorChannels_;
    double marginEnergy_;

    void calculatePixelEnergy(const std::shared_ptr<const cv::Mat>& image,
                              std::vector<std::vector<double>>& outPixelEnergy);

    void calculatePixelEnergyForEveryRow(const std::shared_ptr<const cv::Mat>& image,
                                         std::vector<std::vector<double>>& outPixelEnergy,
                                         bool bDoOddColumns);

    void calculatePixelEnergyForEveryColumn(const std::shared_ptr<const cv::Mat>& image,
                                            std::vector<std::vector<double>>& outPixelEnergy,
                                            bool bDoOddRows);

    inline static const bool bRegistered_ =
        SeamCarverProcessorFactory::getFactoryInstance().registerNewStage(
            EPipelineStageId::STAGE_0, []() {
                return std::dynamic_pointer_cast<ISeamCarverDataProcessor>(
                    std::make_shared<ComputeEnergy>());
            });
};

}  // namespace sc

#endif
