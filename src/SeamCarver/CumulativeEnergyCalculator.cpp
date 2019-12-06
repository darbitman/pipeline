#include "CumulativeEnergyCalculator.hpp"

namespace seamcarver
{
void CumulativeEnergyCalculator::calculatePixelEnergy(
    const IArray2D<SeamCarverData::PixelEnergyType>& pixelEnergy,
    IArray2D<SeamCarverData::PixelEnergyType>& cumulativeEnergyToPixel,
    IArray2D<SeamCarverData::PixelColumnType>& columnToPixel, IArray2D<bool>& markedPixels) const
    noexcept
{
    auto dimensions = pixelEnergy.size();

    size_t rightColumn = dimensions.second - 1;

    size_t numRows = dimensions.first;
    size_t numColumns = dimensions.second;

    SeamCarverData::PixelEnergyType maximumEnergy{0xFFFF};

    for (size_t row = 1; row < numRows; ++row)
    {
        decltype(maximumEnergy) cumulativeEnergyAboveLeft = maximumEnergy;
        decltype(maximumEnergy) cumulativeEnergyAbove = cumulativeEnergyToPixel.at(row - 1, 0);
        decltype(maximumEnergy) cumulativeEnergyAboveRight =
            numColumns > 1 ? cumulativeEnergyToPixel.at(row - 1, 1) : maximumEnergy;

        bool markedAboveLeft = true;
        bool markedAbove = markedPixels.at(row - 1, 0);
        bool markedAboveRight = numColumns > 1 ? markedPixels.at(row - 1, 1) : true;

        for (size_t column = 0; column < numColumns; ++column)
        {
            decltype(maximumEnergy) minCumulativeParentEnergyFound = maximumEnergy;
            SeamCarverData::PixelColumnType minParentEnergyColumn = -1;

            // ignore current pixel if it has been marked part of a seam already
            if (!markedPixels.at(row, column))
            {
                // check left/above
                if (!markedAboveLeft && cumulativeEnergyAboveLeft < minCumulativeParentEnergyFound)
                {
                    minCumulativeParentEnergyFound = cumulativeEnergyAboveLeft;
                    minParentEnergyColumn = column - 1;
                }

                // check above
                if (!markedAbove && cumulativeEnergyAbove < minCumulativeParentEnergyFound)
                {
                    minCumulativeParentEnergyFound = cumulativeEnergyAbove;
                    minParentEnergyColumn = column;
                }

                // check right/above
                if (!markedAboveRight &&
                    cumulativeEnergyAboveRight < minCumulativeParentEnergyFound)
                {
                    minCumulativeParentEnergyFound = cumulativeEnergyAboveRight;
                    minParentEnergyColumn = column + 1;
                }
            }

            // shift to the left
            cumulativeEnergyAboveLeft = cumulativeEnergyAbove;
            markedAboveLeft = markedAbove;
            cumulativeEnergyAbove = cumulativeEnergyAboveRight;
            markedAbove = markedAboveRight;

            // retrieve info for pixel above/right
            if (numColumns > 1 && column < numColumns - 2)
            {
                markedAboveRight = markedPixels.at(row - 1, column + 2);
                cumulativeEnergyAboveRight = cumulativeEnergyToPixel.at(row - 1, column + 2);
            }

            // assign cumulative energy to current pixel
            if (minParentEnergyColumn == -1)
            {
                // current pixel is unreachable from parent pixels since they are all unreachable
                // themselves
                cumulativeEnergyToPixel.at(row, column) = maximumEnergy;
            }
            else
            {
                // cumulative energy to reach current pixel is equal to the energy of the current
                // pixel plus the minimum cumulative energy to one of the current pixel's parent
                // pixels
                cumulativeEnergyToPixel.at(row, column) =
                    minCumulativeParentEnergyFound + pixelEnergy.at(row, column);
            }

            // save the column used to reach the current pixel
            // either this is -1 if parent is unreachable, or it's the column of one of the three
            // parent pixels
            columnToPixel.at(row, column) = minParentEnergyColumn;
        }
    }
}

}  // namespace seamcarver