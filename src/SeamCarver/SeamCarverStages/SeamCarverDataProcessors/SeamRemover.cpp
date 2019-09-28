#include "SeamRemover.hpp"

#include <memory>

#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

namespace pipeline
{
SeamRemover::SeamRemover() {}

SeamRemover::~SeamRemover() {}

void SeamRemover::runSeamCarverProcessor(BasePipelineData* pData)
{
    auto& data = *static_cast<VerticalSeamCarverData*>(pData);

    // each row of seams stores an ordered queue of pixels to remove in that row
    //   starting with the min number column
    // each time a new column is encountered, move the pixels to the right of it
    //   (up until the next column number) to the left by the number of pixels already
    //   removed

    auto& discoveredSeams = data.getDiscoveredSeamsVectorOfPqs();

    size_t colToRemove = 0;
    size_t numSeamsRemoved = 0;
    size_t numRows = data.getNumberOfRows();
    size_t numColumns = data.getNumberOfColumns();
    size_t numColorChannels = data.getNumberOfColorChannels();

    /// REMOVE PIXELS FOR EVERY ROW
    for (size_t row = 0; row < numRows; row++)
    {
        // seamRecalculationCount the number of seams to the left of the current pixel
        //   to indicate how many spaces to move pixels that aren't being removed to the
        //   left
        numSeamsRemoved = 0;
        // loop through all pixels to remove in current row
        while (!discoveredSeams[row].empty())
        {
            numSeamsRemoved++;
            // column location of pixel to remove in row
            colToRemove = discoveredSeams[row].top();
            discoveredSeams[row].pop();

            // mark right endpoint/next pixel column
            size_t rightColBorder =
                (discoveredSeams[row].empty() ? numColumns : discoveredSeams[row].top());
            // starting at the column to the right of the column to remove,
            //      move the pixel to the left, by the number of seams to the left of the
            //      pixel, until the right end point which is either the last column or the
            //      next column to remove whichever comes first
            for (size_t column = colToRemove + 1; column < rightColBorder; column++)
            {
                for (size_t j = 0; j < numColorChannels; j++)
                {
                    // TODO
                    // data->bgr[j].at<unsigned char>(row, column - numSeamsRemoved) =
                    //     data->bgr[j].at<unsigned char>(row, column);
                }
            }
        }
    }

    /*** SHRINK IMAGE SINCE THE IMPORTANT SEAMS WERE SHIFTED LEFT ***/
    for (size_t channel = 0; channel < numColorChannels; channel++)
    {
        // TODO
        // data->bgr[channel] = data->bgr[channel].colRange(0, data->numColumns_ - numSeamsRemoved);
    }
}

}  // namespace pipeline
