#ifndef VERTICALSEAMCARVERDATA_HPP
#define VERTICALSEAMCARVERDATA_HPP

#include <cstdint>
#include <memory>
#include <opencv2/core.hpp>
#include <vector>

#include "BasePipelineData.hpp"
#include "ConstSizePriorityQueue.hpp"

namespace sc
{
// forward declare class;
class PixelEnergyCalculator2D;

struct VerticalSeamCarverData : public BasePipelineData
{
public:
    struct FrameNumberLessComparator
    {
        bool operator()(const BasePipelineData* p1, const BasePipelineData* p2)
        {
            return (((VerticalSeamCarverData*)p1)->getFrameNumber() < ((VerticalSeamCarverData*)p2)->getFrameNumber());
        }
    };

    explicit VerticalSeamCarverData(double marginEnergy = 390150.0);

    ~VerticalSeamCarverData();

    /**
     * @brief initialize internal data stores
     */
    void initialize();

    /**
     * @brief save the image to internal data store
     * @param image the image to store internally for processing
     */
    void saveImage(std::shared_ptr<cv::Mat> image);

    /**
     * @brief returns the saved image
     * @bool bClearLocalData a flag that indicates whether or not to clear the underlying saved
     * image
     * @return std::shared_ptr<cv::Mat>
     */
    std::shared_ptr<cv::Mat> getSavedImage(bool bClearLocalData = true);

    /*
     * @brief reset internal data structures to their clean state
     */
    void resetData();

    /**
     * @brief separates individual color channels and stores the result into bgr
     */
    void separateChannels();

    /*
     * @brief check if internal vector dimensions are the same as of the image
     * @return bool returns true if internal data structures are of the same dimensions as the
     * internal image
     */
    bool areImageDimensionsVerified() const;

    /**
     * @brief set a new frame number for this frame
     * @param newFrameNumber the value to set the frame number for this frame
     */
    void setFrameNumber(uint32_t newFrameNumber);

    /**
     * @brief increments the frame number by 1
     */
    void incrementFrameNumber();

    /**
     * @brief returns the frame number of this frame
     * @return uint32_t
     */
    uint32_t getFrameNumber() const;

    // flag if internal data structures need their memory and values initialized
    bool bNeedToInitializeLocalData;

    // vector to store pixels that have been previously markedPixels for removal
    // will ignore these markedPixels pixels when searching for a new seam
    std::vector<std::vector<bool>> markedPixels;

    // individual pixel energy
    std::vector<std::vector<double>> pixelEnergy;

    // vector of min oriented priority queues that store the location of the pixels to remove
    // the index to the vector corresponds to the rows
    // the column index is stored in the PQ
    std::vector<ConstSizePriorityQueue<int32_t>> discoveredSeams;

    // store cumulative energy to each pixel
    std::vector<std::vector<double>> totalEnergyTo;

    // store the column of the pixel in the "previous" row to get to the current pixel
    std::vector<std::vector<int32_t>> columnTo;

    // store the current seam being discovered
    std::vector<size_t> currentSeam;

    // vector to hold image color channels separately
    std::vector<cv::Mat> bgr;

    // image dimensions
    size_t numRows_;
    size_t numColumns_;
    size_t bottomRow_;
    size_t rightColumn_;
    size_t numColorChannels_;

    // number of pixels per seam
    size_t seamLength_;

    // value of positive infinity
    double posInf_;

    // number of seams to remove (updated every run)
    size_t numSeamsToRemove_;

    // default energy at the borders of the image
    const double marginEnergy_;

private:
    uint32_t frameNumber_;

    // stores the image and output result
    std::shared_ptr<cv::Mat> savedImage_;
};
}  // namespace sc

#endif
