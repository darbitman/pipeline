#include "ComputeEnergy.hpp"

#include <memory>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

#include "VerticalSeamCarverData.hpp"

using cv::Mat;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::ref;
using std::shared_ptr;
using std::thread;
using std::vector;

namespace sc
{
ComputeEnergy::ComputeEnergy() {}

ComputeEnergy::~ComputeEnergy() {}

void ComputeEnergy::runSeamCarverProcessor(shared_ptr<VerticalSeamCarverData> pData)
{
    // TODO

    // set local data members for the computation
    numRows_ = pData->getNumberOfRows();
    numColumns_ = pData->getNumberOfColumns();
    bottomRow_ = pData->getBottomRowIndex();
    rightColumn_ = pData->getRightColumnIndex();
    numColorChannels_ = pData->getNumberOfColorChannels();
    marginEnergy_ = pData->getEdgePixelEnergy();

    calculatePixelEnergy(pData->getSavedImage(), pData->getPixelEnergy2DVector());
}

void ComputeEnergy::calculatePixelEnergy(const shared_ptr<const Mat>& image,
                                         vector<vector<double>>& outPixelEnergy)
{
    // if more columns, split calculation into 2 operations to calculate for every row
    if (numColumns_ >= numRows_)
    {
        thread thread1(&ComputeEnergy::calculatePixelEnergyForEveryRow, this, ref(image),
                       ref(outPixelEnergy), true);
        thread thread2(&ComputeEnergy::calculatePixelEnergyForEveryRow, this, ref(image),
                       ref(outPixelEnergy), false);
        while (!thread1.joinable())
            ;
        thread1.join();
        while (!thread2.joinable())
            ;
        thread2.join();
    }
    // otherwise, if more rows, split calculation into 2 operations to calculate for every column
    else
    {
        thread thread1(&ComputeEnergy::calculatePixelEnergyForEveryColumn, this, ref(image),
                       ref(outPixelEnergy), true);
        thread thread2(&ComputeEnergy::calculatePixelEnergyForEveryColumn, this, ref(image),
                       ref(outPixelEnergy), false);
        while (!thread1.joinable())
            ;
        thread1.join();
        while (!thread2.joinable())
            ;
        thread2.join();
    }
}

void ComputeEnergy::calculatePixelEnergyForEveryRow(const shared_ptr<const Mat>& image,
                                                    vector<vector<double>>& outPixelEnergy,
                                                    bool bDoOddColumns)
{
    vector<Mat> imageByChannel;
    imageByChannel.resize(numColorChannels_);

    // if color channels use cv::split
    // otherwise if grayscale use cv::extractChannel
    if (numColorChannels_ == 3)
    {
        split(*image, imageByChannel);
    }
    else if (numColorChannels_ == 1)
    {
        extractChannel(*image, imageByChannel[0], 0);
    }
    else
    {
        return;
    }

    // Establish vectors whose size is equal to the number of channels
    // Two vectors used to compute X gradient
    // Don't need them for Y since we are only caching the columns
    // We can just access the pixel values above/below directly to compute the delta
    // TODO replace vectors with a multidimensional vector
    vector<double> xDirection2;
    vector<double> xDirection1;

    xDirection2.resize(numColorChannels_);
    xDirection1.resize(numColorChannels_);

    vector<double> deltaXDirection;
    vector<double> deltaYDirection;

    deltaXDirection.resize(numColorChannels_);
    deltaYDirection.resize(numColorChannels_);

    double deltaSquareX = 0.0;
    double deltaSquareY = 0.0;

    size_t column = 0;
    // compute energy for every row
    // do odd columns and even columns separately in order to leverage cached values to prevent
    // multiple memory accesses
    for (size_t row = 0; row < numRows_; row++)
    {
        /***** ODD COLUMNS *****/
        if (bDoOddColumns)
        {
            // initialize starting column
            column = 1;

            // initialize color values to the left of current pixel
            for (size_t channel = 0; channel < numColorChannels_; channel++)
            {
                xDirection1[channel] = imageByChannel[channel].at<uchar>(row, column - 1);
            }

            // Compute energy of odd columns
            for (/* column already initialized */; column < numColumns_; column += 2)
            {
                if (row == 0 || column == 0 || row == bottomRow_ || column == rightColumn_)
                {
                    outPixelEnergy[row][column] = marginEnergy_;
                }
                else
                {
                    // Reset gradients from previous calculation
                    deltaSquareX = 0.0;
                    deltaSquareY = 0.0;

                    // For all channels:
                    // Compute gradients
                    // Compute overall energy by summing both X and Y gradient
                    for (size_t channel = 0; channel < numColorChannels_; channel++)
                    {
                        // get new values to the right
                        xDirection2[channel] = imageByChannel[channel].at<uchar>(row, column + 1);

                        deltaXDirection[channel] = xDirection2[channel] - xDirection1[channel];

                        deltaSquareX += deltaXDirection[channel] * deltaXDirection[channel];

                        deltaYDirection[channel] =
                            imageByChannel[channel].at<uchar>(row + 1, column) -
                            imageByChannel[channel].at<uchar>(row - 1, column);

                        deltaSquareY += deltaYDirection[channel] * deltaYDirection[channel];

                        // shift color values to the left
                        xDirection1[channel] = xDirection2[channel];
                    }
                    outPixelEnergy[row][column] = deltaSquareX + deltaSquareY;
                }
            }
        }
        /***** EVEN COLUMNS *****/
        else
        {
            // initialize starting column
            column = 0;

            // initialize color values to the right of current pixel
            for (size_t Channel = 0; Channel < numColorChannels_; Channel++)
            {
                xDirection2[Channel] = imageByChannel[Channel].at<uchar>(row, column + 1);
            }

            // Compute energy of odd columns
            for (/* column already initialized */; column < numColumns_; column += 2)
            {
                if (row == 0 || column == 0 || row == bottomRow_ || column == rightColumn_)
                {
                    outPixelEnergy[row][column] = marginEnergy_;
                }
                else
                {
                    // Reset gradient from previous calculation
                    deltaSquareX = 0.0;
                    deltaSquareY = 0.0;

                    // For all channels:
                    // Compute gradients
                    // Compute overall energy by summing both X and Y gradient
                    for (size_t channel = 0; channel < numColorChannels_; channel++)
                    {
                        // shift color values to the left
                        xDirection1[channel] = xDirection2[channel];

                        // get new values to the right
                        xDirection2[channel] = imageByChannel[channel].at<uchar>(row, column + 1);
                        deltaXDirection[channel] = xDirection2[channel] - xDirection1[channel];

                        deltaSquareX += deltaXDirection[channel] * deltaXDirection[channel];

                        deltaYDirection[channel] =
                            imageByChannel[channel].at<uchar>(row + 1, column) -
                            imageByChannel[channel].at<uchar>(row - 1, column);

                        deltaSquareY += deltaYDirection[channel] * deltaYDirection[channel];
                    }
                    outPixelEnergy[row][column] = deltaSquareX + deltaSquareY;
                }
            }
        }
    }
}

void ComputeEnergy::calculatePixelEnergyForEveryColumn(const shared_ptr<const Mat>& image,
                                                       vector<vector<double>>& outPixelEnergy,
                                                       bool bDoOddRows)
{
    vector<Mat> imageByChannel;
    imageByChannel.resize(numColorChannels_);

    // if color channels use cv::split
    // otherwise if grayscale use cv::extractChannel
    if (numColorChannels_ == 3)
    {
        split(*image, imageByChannel);
    }
    else if (numColorChannels_ == 1)
    {
        extractChannel(*image, imageByChannel[0], 0);
    }
    else
    {
        return;
    }

    // Establish vectors whose size is equal to the number of channels
    // Two vectors used to compute X gradient
    // Don't need them for Y since we are only caching the columns
    // We can just access the pixel values above/below directly to compute the delta
    // TODO replace vectors with a multidimensional vector
    vector<double> yDirection2;
    vector<double> yDirection1;

    yDirection2.resize(numColorChannels_);
    yDirection1.resize(numColorChannels_);

    vector<double> deltaXDirection;
    vector<double> deltaYDirection;

    deltaXDirection.resize(numColorChannels_);
    deltaYDirection.resize(numColorChannels_);

    double deltaSquareX = 0.0;
    double deltaSquareY = 0.0;

    size_t row = 0;
    // compute energy for every column
    // do odd rows and even rows separately in order to leverage cached values
    // to prevent multiple memory accesses
    for (size_t column = 0; column < numColumns_; column++)
    {
        /***** ODD ROWS *****/
        if (bDoOddRows)
        {
            // initialize starting row
            row = 1;

            // initialize color values above the current pixel
            for (size_t channel = 0; channel < numColorChannels_; channel++)
            {
                yDirection1[channel] = imageByChannel[channel].at<uchar>(row - 1, column);
            }

            // Compute energy of odd rows
            for (/* row was already initialized */; row < numRows_; row += 2)
            {
                if (row == 0 || column == 0 || row == bottomRow_ || column == rightColumn_)
                {
                    outPixelEnergy[row][column] = marginEnergy_;
                }
                else
                {
                    // Reset gradients from previous calculation
                    deltaSquareX = 0.0;
                    deltaSquareY = 0.0;

                    // For all channels:
                    // Compute gradients
                    // Compute overall energy by summing both X and Y gradient
                    for (size_t channel = 0; channel < numColorChannels_; channel++)
                    {
                        // get new values below the current pixel
                        yDirection2[channel] = imageByChannel[channel].at<uchar>(row + 1, column);

                        deltaYDirection[channel] = yDirection2[channel] - yDirection1[channel];

                        deltaSquareY = deltaYDirection[channel] * deltaYDirection[channel];

                        deltaXDirection[channel] =
                            imageByChannel[channel].at<uchar>(row, column + 1) -
                            imageByChannel[channel].at<uchar>(row, column - 1);

                        deltaSquareX += deltaXDirection[channel] * deltaXDirection[channel];

                        // shift color values up
                        yDirection1[channel] = yDirection2[channel];
                    }
                    outPixelEnergy[row][column] = deltaSquareX + deltaSquareY;
                }
            }
        }
        /***** EVEN ROWS *****/
        else
        {
            // initialize starting row
            row = 0;

            // initialize color values below the current pixel
            for (size_t channel = 0; channel < numColorChannels_; channel++)
            {
                yDirection2[channel] = imageByChannel[channel].at<uchar>(row + 1, column);
            }

            // Compute energy of odd rows
            for (/* row was already initialized */; row < numRows_; row += 2)
            {
                if (row == 0 || column == 0 || row == bottomRow_ || column == rightColumn_)
                {
                    outPixelEnergy[row][column] = marginEnergy_;
                }
                else
                {
                    // Reset gradient from previous calculation
                    deltaSquareX = 0.0;
                    deltaSquareY = 0.0;

                    // For all channels:
                    // Compute gradients
                    // Compute overall energy by summing both X and Y gradient
                    for (size_t channel = 0; channel < numColorChannels_; channel++)
                    {
                        // shift color values up
                        yDirection1[channel] = yDirection2[channel];

                        // get new values below the current pixel
                        yDirection2[channel] = imageByChannel[channel].at<uchar>(row + 1, column);
                        deltaYDirection[channel] = yDirection2[channel] - yDirection1[channel];

                        deltaSquareY += deltaYDirection[channel] * deltaYDirection[channel];

                        deltaXDirection[channel] =
                            imageByChannel[channel].at<uchar>(row, column + 1) -
                            imageByChannel[channel].at<uchar>(row, column - 1);

                        deltaSquareX += deltaXDirection[channel] * deltaXDirection[channel];
                    }
                    outPixelEnergy[row][column] = deltaSquareX + deltaSquareY;
                }
            }
        }
    }
}

}  // namespace sc
