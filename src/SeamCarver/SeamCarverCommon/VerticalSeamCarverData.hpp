#pragma once

#include <cstdint>
#include <memory>
#include <opencv2/core.hpp>
#include <vector>

#include "BasePipelineData.hpp"
#include "PriorityQueue.hpp"

namespace pipeline
{
class VerticalSeamCarverData : public BasePipelineData
{
  public:
    explicit VerticalSeamCarverData(double marginEnergy = 390150.0);

    virtual ~VerticalSeamCarverData() = default;

    /// @brief initialize internal data stores
    void initialize();

    //  void setNeedToInitializeFlag();

    //  void resetNeedToInitializeFlag();

    //  bool getNeedToInitializeFlag();

    /// @brief save the image to internal data store
    /// @param image the image to store internally for processing
    void saveImage(std::unique_ptr<cv::Mat>& image);

    /// @brief returns the saved image
    /// @bool bReleaseOwnership indicates whether or not to release ownership of the image
    /// @return std::unique_ptr<cv::Mat>
    std::unique_ptr<cv::Mat> getSavedImage(bool bReleaseOwnership = true);

    /// @brief reset internal data structures to their clean state
    void resetData();

    /// @brief separates individual color channels from the saved image
    void separateChannels();

    /// @brief check if internal vector dimensions are the same as of the image
    /// @return bool returns true if internal data structures are of the same dimensions as the
    /// internal image
    bool areImageDimensionsVerified() const
    {
        return ((size_t)savedImage_->rows == numRows_ && (size_t)savedImage_->cols == numColumns_);
    }

    /// @brief set a new frame number for this frame
    /// @param newFrameNumber the value to set the frame number for this frame
    void setFrameNumber(uint32_t newFrameNumber) noexcept { frameNumber_ = newFrameNumber; }

    /// @brief increments the frame number by 1
    void incrementFrameNumber() noexcept { ++frameNumber_; }

    /// @brief returns the frame number of this frame
    /// @return uint32_t
    uint32_t getFrameNumber() const noexcept { return frameNumber_; }

    size_t getNumberOfRows() const noexcept { return numRows_; }

    size_t getNumberOfColumns() const noexcept { return numColumns_; }

    size_t getBottomRowIndex() const noexcept { return bottomRow_; }

    size_t getRightColumnIndex() const noexcept { return rightColumn_; }

    size_t getNumberOfColorChannels() const noexcept { return numColorChannels_; }

    //  void setSeamLength(size_t seamLength);

    //  size_t getSeamLength() const noexcept;

    void setNumberOfSeamsToRemove(size_t numberOfSeamsToRemove) noexcept
    {
        numSeamsToRemove_ = numberOfSeamsToRemove;
    }

    size_t getNumberOfSeamsToRemove() const noexcept { return numSeamsToRemove_; }

    double getEdgePixelEnergy() const noexcept { return marginEnergy_; }

    std::vector<std::vector<bool>>& getMarkedPixel2DVector();

    std::vector<std::vector<double>>& getPixelEnergy2DVector();

    std::vector<PriorityQueue<int32_t>>& getDiscoveredSeamsVectorOfPqs();

    std::vector<std::vector<double>>& getTotalEnergyToPixel2DVector();

    std::vector<std::vector<int32_t>>& getPreviousColumnToCurrentPixel2DVector();

    void mergeChannelsAndStoreToSavedImage();

    double getPositiveInfinity() const noexcept { return posInf_; }

    /**********************************************************************************/
    // vector of min oriented priority queues that store the location of the pixels to remove
    // the index to the vector corresponds to the rows
    // the column index is stored in the PQ
    std::vector<PriorityQueue<int32_t>> discoveredSeams;

    // store the current seam being discovered
    std::vector<size_t> currentSeam;

    // vector to hold image color channels separately
    std::vector<cv::Mat> bgr;

    // number of pixels per seam
    size_t seamLength_;

    // value of positive infinity
    double posInf_;

    // number of seams to remove (updated every run)
    size_t numSeamsToRemove_;

    // default energy at the borders of the image
    const double marginEnergy_;

  private:
    // flag if internal data structures need their memory and values initialized
    bool bNeedToInitializeLocalData;

    // image dimensions
    size_t numRows_;
    size_t numColumns_;
    size_t bottomRow_;
    size_t rightColumn_;
    size_t numColorChannels_;

    uint32_t frameNumber_;

    // stores the image and output result
    std::unique_ptr<cv::Mat> savedImage_;

    // vector to store pixels that have been previously markedPixels for removal
    // will ignore these markedPixels pixels when searching for a new seam
    std::vector<std::vector<bool>> markedPixels;

    // individual pixel energy
    std::vector<std::vector<double>> pixelEnergy;

    // store cumulative energy to each pixel
    std::vector<std::vector<double>> totalEnergyTo;

    // store the column of the pixel in the "previous" row to get to the current pixel
    std::vector<std::vector<int32_t>> columnTo;
};
}  // namespace pipeline
