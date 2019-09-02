#include "CumulativePathEnergy.hpp"

#include <memory>

#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

namespace sc
{
void CumulativePathEnergy::runSeamCarverProcessor(BasePipelineData* pData)
{
    VerticalSeamCarverData* pSeamCarverData = static_cast<VerticalSeamCarverData*>(pData);

    numRows_ = pSeamCarverData->getNumberOfRows();
    numColumns_ = pSeamCarverData->getNumberOfColumns();
    marginEnergy_ = pSeamCarverData->marginEnergy_;
    posInf_ = posInf_;

    auto& markedPixels = pSeamCarverData->getMarkedPixel2DVector();
    auto& totalEnergyTo = pSeamCarverData->getTotalEnergyToPixel2DVector();
    auto& columnTo = pSeamCarverData->getPreviousColumnToCurrentPixel2DVector();
    auto& pixelEnergy = pSeamCarverData->getPixelEnergy2DVector();

    // initialize top row
    for (size_t column = 0; column < numColumns_; ++column)
    {
        // if previously markedPixels, set its energy to +INF
        if (markedPixels[0][column])
        {
            totalEnergyTo[0][column] = posInf_;
        }
        else
        {
            totalEnergyTo[0][column] = marginEnergy_;
        }

        columnTo[0][column] = -1;
    }

    // cache the total energy to the pixels up/left, directly above, and up/right
    //   instead of accessing memory for the same pixels
    // shift energy values to the left and access memory only once
    // SHIFT OPERATION:
    //   left/above <== directly above
    //   directly above <== right/above
    //   right/above = access new memory
    double energyUpLeft = posInf_;
    double energyUp = posInf_;
    double energyUpRight = posInf_;

    double minEnergy = posInf_;
    int32_t minEnergyColumn = -1;

    for (size_t row = 1; row < numRows_; row++)
    {
        energyUpLeft = posInf_;
        energyUp = totalEnergyTo[row - 1][0];
        energyUpRight = numColumns_ > 1 ? totalEnergyTo[row - 1][1] : posInf_;

        bool markedUpLeft = true;
        bool markedUp = markedPixels[row - 1][0];
        bool markedUpRight = numColumns_ > 1 ? markedPixels[row - 1][1] : true;

        // find minimum energy path from previous row to every pixel in the current row
        for (size_t column = 0; column < numColumns_; ++column)
        {
            // initialize min energy to +INF and initialize the previous column to -1 to set invalid
            // state
            minEnergy = posInf_;
            minEnergyColumn = -1;

            // save some cycles by not doing any comparisons if the current pixel has been
            // previously marked
            if (!markedPixels[row][column])
            {
                // check above
                if (!markedUp && energyUp < minEnergy)
                {
                    minEnergy = energyUp;
                    minEnergyColumn = column;
                }

                // check if right/above is min
                if (column < numColumns_ - 1)
                {
                    if (!markedUpRight && energyUpRight < minEnergy)
                    {
                        minEnergy = energyUpRight;
                        minEnergyColumn = column + 1;
                    }
                }

                // check if left/above is min
                if (column > 0)
                {
                    if (!markedUpLeft && energyUpLeft < minEnergy)
                    {
                        minEnergy = energyUpLeft;
                        minEnergyColumn = column - 1;
                    }
                }
            }

            // shift energy to the left
            energyUpLeft = energyUp;
            markedUpLeft = markedUp;
            energyUp = energyUpRight;
            markedUp = markedUpRight;

            // for pixel to the right/above, get its marked flag and get the total energy to it
            if (numColumns_ > 1 && column < numColumns_ - 2)
            {
                energyUpRight = totalEnergyTo[row - 1][column + 2];
                markedUpRight = markedPixels[row - 1][column + 2];
            }

            // assign cumulative energy to current pixel and save the column of the parent pixel
            if (minEnergyColumn == -1)
            {
                // current pixel is unreachable from parent pixels
                totalEnergyTo[row][column] = posInf_;
            }
            else
            {
                totalEnergyTo[row][column] = minEnergy + pixelEnergy[row][column];
            }

            // this is either -1 or a valid column
            columnTo[row][column] = minEnergyColumn;
        }
    }
}

}  // namespace sc
