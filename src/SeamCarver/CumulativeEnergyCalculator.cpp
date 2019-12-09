#include "CumulativeEnergyCalculator.hpp"

namespace seamcarver
{
void CumulativeEnergyCalculator::calculateCumulativePixelEnergy(
    const IArray2D<PixelEnergyType>& pixelEnergy,
    IArray2D<PixelEnergyType>& cumulativeEnergyToPixel, IArray2D<PixelColumnType>& columnToPixel,
    IArray2D<bool>& markedPixels) const noexcept
{
    auto [numRows, numColumns] = pixelEnergy.size();

    size_t rightColumn = numColumns - 1;

    for (size_t row = 1; row < numRows; ++row)
    {
        PixelEnergyType cumulativeEnergyAboveLeft = MAXIMUM_ENERGY;
        PixelEnergyType cumulativeEnergyAbove = cumulativeEnergyToPixel.at(row - 1, 0);
        PixelEnergyType cumulativeEnergyAboveRight =
            numColumns > 1 ? cumulativeEnergyToPixel.at(row - 1, 1) : MAXIMUM_ENERGY;

        bool markedAboveLeft = true;
        bool markedAbove = markedPixels.at(row - 1, 0);
        bool markedAboveRight = numColumns > 1 ? markedPixels.at(row - 1, 1) : true;

        for (size_t column = 0; column < numColumns; ++column)
        {
            PixelEnergyType minCumulativeParentEnergyFound = MAXIMUM_ENERGY;
            PixelColumnType minParentEnergyColumn = -1;

            // ignore current pixel if it has been marked part of a seam already
            if (!markedPixels.at(row, column))
            {
                // check left/above
                TryUpdateMinimumEnergy(
                    !markedAboveLeft && cumulativeEnergyAboveLeft < minCumulativeParentEnergyFound,
                    minCumulativeParentEnergyFound, cumulativeEnergyAboveLeft,
                    minParentEnergyColumn, column - 1);

                // check above
                TryUpdateMinimumEnergy(
                    !markedAboveLeft && cumulativeEnergyAboveLeft < minCumulativeParentEnergyFound,
                    minCumulativeParentEnergyFound, cumulativeEnergyAboveLeft,
                    minParentEnergyColumn, column);

                // check right/above
                TryUpdateMinimumEnergy(
                    !markedAboveLeft && cumulativeEnergyAboveLeft < minCumulativeParentEnergyFound,
                    minCumulativeParentEnergyFound, cumulativeEnergyAboveLeft,
                    minParentEnergyColumn, column - 1);
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

            // // assign cumulative energy to current pixel
            // if (minParentEnergyColumn == -1)
            // {
            //     // current pixel is unreachable from parent pixels since they are all unreachable
            //     // themselves
            //     cumulativeEnergyToPixel.at(row, column) = MAXIMUM_ENERGY;
            // }
            // else
            // {
            //     // cumulative energy to reach current pixel is equal to the energy of the current
            //     // pixel plus the minimum cumulative energy to one of the current pixel's parent
            //     // pixels
            //     cumulativeEnergyToPixel.at(row, column) =
            //         minCumulativeParentEnergyFound + pixelEnergy.at(row, column);
            // }

            bool badMinParentEnergyColumn = (minParentEnergyColumn == -1);
            cumulativeEnergyToPixel.at(row, column) =
                ((-static_cast<SignedPixelEnergyType>(badMinParentEnergyColumn) & MAXIMUM_ENERGY) |
                 (((static_cast<SignedPixelEnergyType>(badMinParentEnergyColumn) - 1) &
                   (minCumulativeParentEnergyFound + pixelEnergy.at(row, column)))));

            // save the column used to reach the current pixel
            // either this is -1 if parent is unreachable, or it's the column of one of the three
            // parent pixels
            columnToPixel.at(row, column) = minParentEnergyColumn;
        }
    }
}

void CumulativeEnergyCalculator::TryUpdateMinimumEnergy(bool flag, PixelEnergyType& minEnergy,
                                                        PixelEnergyType newEnergy,
                                                        PixelColumnType& minEnergyColumn,
                                                        PixelColumnType newColumn) const noexcept
{
    // if flag is true, update update minEnergy and minEnergyColumn
    // if flag is false, preserve old values
    minEnergy = ((-static_cast<SignedPixelEnergyType>(flag)) & newEnergy) |
                ((static_cast<SignedPixelEnergyType>(flag) - 1) & minEnergy);

    minEnergyColumn = ((-static_cast<PixelColumnType>(flag)) & newColumn) |
                      ((static_cast<PixelColumnType>(flag) - 1) & minEnergyColumn);
};

}  // namespace seamcarver