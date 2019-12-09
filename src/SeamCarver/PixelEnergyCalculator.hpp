#pragma once

#include "IArray2D.hpp"
#include "SeamCarverCommon.hpp"

namespace seamcarver
{
class PixelEnergyCalculator
{
  public:
    /// @brief This method computes the pixel energy at each [row, column] in the pixelMatrix.
    /// This method expects the pixelMatrix to be a B/W or a single color channel
    /// @param pixelMatrix A 2D pixelMatrix that represents a single color channel, whose values
    /// range from 0 to 765. (765 is the sum of the maximum value of each color channel, assuming a
    /// maximum value of 255 for each of the RGB color channels)
    /// @param outPixelEnergy Output parameter where the calculated pixel energy will be stored.The
    /// edge pixel energy has already been calculated and initialized to its default value.
    void calculatePixelEnergy(const IArray2D<PixelColorType>& pixelMatrix,
                              IArray2D<PixelEnergyType>& outPixelEnergy) const noexcept;

  private:
    /// @brief calculate energy for every row, but starting column can be changed. Recommended to
    /// call this with two threads. One to compute odd columns and another to compute even columns.
    /// For odd columns, startingColumn should be set to 1. For even columns, startingColumn should
    /// be set to 2 (0 is the edge). Same goes for startingRow.
    /// @param pixelMatrix Pixel data
    /// @param outPixelEnergy Output parameter that stores the result of calculating the pixel
    /// energy for every pixel in pixelMatrix
    /// @param startingRow
    /// @param startingColumn
    void calculateEnergyForEveryOtherColumn(const IArray2D<PixelColorType>& pixelMatrix,
                                            IArray2D<PixelEnergyType>& outPixelEnergy,
                                            size_t startingRow, size_t startingColumn) const
        noexcept;
};

}  // namespace seamcarver
