#include "CumulativeEnergyCalculator.hpp"

namespace seamcarver
{
void CumulativeEnergyCalculator::calculateCumulativePixelEnergy(
    const IArray2D<SeamCarverData::PixelEnergyType>& pixelEnergy,
    IArray2D<SeamCarverData::PixelEnergyType>& cumulativeEnergyToPixel,
    IArray2D<SeamCarverData::PixelColumnType>& columnToPixel, IArray2D<bool>& markedPixels) const
    noexcept
{
    auto [numRows, numColumns] = pixelEnergy.size();

    size_t rightColumn = numColumns - 1;

    EnergyType maximumEnergy{0xFFFF};

    for (size_t row = 1; row < numRows; ++row)
    {
        EnergyType cumulativeEnergyAboveLeft = maximumEnergy;
        EnergyType cumulativeEnergyAbove = cumulativeEnergyToPixel.at(row - 1, 0);
        EnergyType cumulativeEnergyAboveRight =
            numColumns > 1 ? cumulativeEnergyToPixel.at(row - 1, 1) : maximumEnergy;

        bool markedAboveLeft = true;
        bool markedAbove = markedPixels.at(row - 1, 0);
        bool markedAboveRight = numColumns > 1 ? markedPixels.at(row - 1, 1) : true;

        for (size_t column = 0; column < numColumns; ++column)
        {
            EnergyType minCumulativeParentEnergyFound = maximumEnergy;
            ColumnType minParentEnergyColumn = -1;

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
            //     cumulativeEnergyToPixel.at(row, column) = maximumEnergy;
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
                ((-static_cast<SignedEnergyType>(badMinParentEnergyColumn) & maximumEnergy) |
                 (((static_cast<SignedEnergyType>(badMinParentEnergyColumn) - 1) &
                   (minCumulativeParentEnergyFound + pixelEnergy.at(row, column)))));

            // save the column used to reach the current pixel
            // either this is -1 if parent is unreachable, or it's the column of one of the three
            // parent pixels
            columnToPixel.at(row, column) = minParentEnergyColumn;
        }
    }
}

void CumulativeEnergyCalculator::TryUpdateMinimumEnergy(bool flag, EnergyType& minEnergy,
                                                        EnergyType newEnergy,
                                                        ColumnType& minEnergyColumn,
                                                        ColumnType newColumn) const noexcept
{
    // if flag is true, update update minEnergy and minEnergyColumn
    // if flag is false, preserve old values
    minEnergy = ((-static_cast<SignedEnergyType>(flag)) & newEnergy) |
                ((static_cast<SignedEnergyType>(flag) - 1) & minEnergy);

    minEnergyColumn = ((-static_cast<ColumnType>(flag)) & newColumn) |
                      ((static_cast<ColumnType>(flag) - 1) & minEnergyColumn);
};

}  // namespace seamcarver