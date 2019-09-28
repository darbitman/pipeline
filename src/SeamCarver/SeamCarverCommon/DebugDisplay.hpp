#ifndef DEBUGDISPLAY_HPP
#define DEBUGDISPLAY_HPP

#include <opencv2/core.hpp>
#include <vector>

namespace pipeline
{
class DebugDisplay
{
public:
    DebugDisplay();

    /**
     * @brief Converts a 2D std::vector of ValueType (e.g. double) to a grayscale cv::Mat internally
     and displays it
     * @param InputVector: grayscale representation of an image
     * @param NormalizationFactor: Factor by which to normalize the values such that any value is
            no larger than 1.0
     */
    template <typename ValueType>
    bool Display2DVector(const std::vector<std::vector<ValueType>>& InputVector,
                         ValueType NormalizationFactor);

    void displayMatrix(const cv::Mat& img);

    /**
     * @brief
     * @param
     * @param
     * @param
     */
    bool MarkPixelsAndDisplay(const std::vector<std::vector<bool>>& PixelsToMark,
                              const cv::Mat& ImageToMark, uchar Color = 255);

private:
    void WaitForEscKey() const;
};
}  // namespace pipeline

sc::DebugDisplay::DebugDisplay() {}

template <typename ValueType>
bool sc::DebugDisplay::Display2DVector(const std::vector<std::vector<ValueType>>& InputVector,
                                       ValueType NormalizationFactor)
{
    if (!(InputVector.size() > 0 && InputVector[0].size() > 0))
    {
        return false;
    }

    // create an output matrix of the same dimensions as input
    cv::Mat output(InputVector.size(), InputVector[0].size(), CV_8UC1);

    for (uint32_t Row = 0; Row < InputVector.size(); Row++)
    {
        for (uint32_t Column = 0; Column < InputVector[0].size(); Column++)
        {
            output.at<uchar>(Row, Column) = (uchar)(InputVector[Row][Column] / NormalizationFactor *
                                                    ((2 << ((sizeof(uchar) * 8) - 1)) - 1));
        }
    }

    sc::namedWindow("DebugDisplay - Display2DVector");
    sc::imshow("DebugDisplay - Display2DVector", output);

    WaitForEscKey();
    return true;
}

void sc::DebugDisplay::displayMatrix(const cv::Mat& img)
{
    sc::namedWindow("DebugDisplay - DisplayMatrix");
    sc::imshow("DebugDisplay - DisplayMatrix", img);

    WaitForEscKey();
}

bool sc::DebugDisplay::MarkPixelsAndDisplay(const std::vector<std::vector<bool>>& PixelsToMark,
                                            const cv::Mat& ImageToMark, uchar color)
{
    size_t numChannels = ImageToMark.channels();
    size_t numColumns = ImageToMark.cols;
    size_t numRows = ImageToMark.rows;

    if (!(PixelsToMark.size() == numRows && PixelsToMark[0].size() == numColumns))
    {
        return false;
    }

    std::vector<cv::Mat> imageByChannel;
    imageByChannel.resize(numChannels);

    // split the cv::Mat into separate channels
    if (numChannels == 3)
    {
        sc::split(ImageToMark, imageByChannel);
    }
    else if (numChannels == 1)
    {
        sc::extractChannel(ImageToMark, imageByChannel[0], 0);
    }
    else
    {
        return false;
    }

    for (size_t row = 0; row < numRows; row++)
    {
        for (size_t column = 0; column < numColumns; column++)
        {
            if (PixelsToMark[row][column])
            {
                for (size_t channel = 0; channel < numChannels; channel++)
                {
                    imageByChannel[channel].at<uchar>(row, column) = color;
                }
            }
        }
    }
    cv::Mat output;
    sc::merge(imageByChannel, output);

    sc::namedWindow("DebugDisplay - MarkPixels");
    sc::imshow("DebugDisplay - MarkPixels", output);
    WaitForEscKey();
    return true;
}

void sc::DebugDisplay::WaitForEscKey() const
{
    while (true)
    {
        if (sc::waitKey(50) == 27)
        {
            break;
        }
    }
}

#endif