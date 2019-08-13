#include "VerticalSeamCarverData.hpp"

#include <cstdint>

using cv::Mat;
using std::make_shared;
using std::numeric_limits;
using std::shared_ptr;

namespace sc
{
VerticalSeamCarverData::VerticalSeamCarverData(double marginEnergy)
    : bNeedToInitializeLocalData(true),
      numRows_(0),
      numColumns_(0),
      bottomRow_(0),
      rightColumn_(0),
      numColorChannels_(0),
      seamLength_(0),
      numSeamsToRemove_(0),
      marginEnergy_(marginEnergy),
      frameNumber_(0)
{
    posInf_ = numeric_limits<double>::max();
}

VerticalSeamCarverData::~VerticalSeamCarverData() {}

void VerticalSeamCarverData::initialize()
{
    // initialize dimension variables
    numRows_ = (size_t)savedImage_->rows;
    numColumns_ = (size_t)savedImage_->cols;
    bottomRow_ = numRows_ - 1;
    rightColumn_ = numColumns_ - 1;
    seamLength_ = numRows_;

    // initialize vectors
    pixelEnergy.resize(numRows_);
    markedPixels.resize(numRows_);
    totalEnergyTo.resize(numRows_);
    columnTo.resize(numRows_);

    for (size_t row = 0; row < numRows_; row++)
    {
        pixelEnergy[row].resize(numColumns_);
        markedPixels[row].resize(numColumns_);
        totalEnergyTo[row].resize(numColumns_);
        columnTo[row].resize(numColumns_);
    }

    currentSeam.resize(seamLength_);
    discoveredSeams.resize(seamLength_);

    // data and vectors just set, so no need to do it again
    bNeedToInitializeLocalData = false;
}

void VerticalSeamCarverData::saveImage(shared_ptr<Mat> image)
{
    savedImage_ = make_shared<Mat>(image->clone());
}

shared_ptr<Mat> VerticalSeamCarverData::getSavedImage(bool bReleaseOwnership)
{
    shared_ptr<Mat> frameToReturn(nullptr);

    // if clearing the underlying data, then need to make sure image doesn't get deallocated or
    // copied over
    if (bReleaseOwnership)
    {
        // swap the pointers between the result image and the nullptr-initialized frameToReturn
        savedImage_.swap(frameToReturn);
    }
    else
    {
        // create a copy to the image
        frameToReturn = savedImage_;
    }

    return frameToReturn;
}

void VerticalSeamCarverData::resetData()
{
    for (size_t row = 0; row < numRows_; ++row)
    {
        for (size_t column = 0; column < numColumns_; ++column)
        {
            markedPixels[row][column] = false;
        }
    }

    // ensure each row's PQ has enough capacity
    for (size_t row = 0; row < seamLength_; ++row)
    {
        // reset priority queue since it could be filled from a previous run
        while (!discoveredSeams[row].empty())
        {
            discoveredSeams[row].pop();
        }
    }
}

void VerticalSeamCarverData::separateChannels()
{
    numColorChannels_ = (size_t)savedImage_->channels();

    if (numColorChannels_ == 3)
    {
        if (bgr.size() != 3)
        {
            bgr.resize(3);
        }

        cv::split(*(savedImage_), bgr);
    }
    else if (numColorChannels_ == 1)
    {
        if (bgr.size() != 1)
        {
            bgr.resize(1);
        }

        cv::extractChannel(*(savedImage_), bgr[0], 0);
    }
    else
    {
        // TODO handle error case
    }
}

bool VerticalSeamCarverData::areImageDimensionsVerified() const
{
    return ((size_t)savedImage_->rows == numRows_ && (size_t)savedImage_->cols == numColumns_);
}

void VerticalSeamCarverData::setFrameNumber(uint32_t newFrameNumber)
{
    frameNumber_ = newFrameNumber;
}

void VerticalSeamCarverData::incrementFrameNumber() { ++frameNumber_; }

uint32_t VerticalSeamCarverData::getFrameNumber() const { return frameNumber_; }
}  // namespace sc