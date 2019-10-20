#pragma once

#include "IArray2D.hpp"
#include "SeamCarverData.hpp"

namespace seamcarver
{
class PixelEnergyCalculator
{
  public:
    /// @brief This method computes the pixel energy at each [row, column] in the matrix.
    /// This method expects the matrix to be a B/W or a single color channel
    /// @param matrix A 2D matrix that represents a single color channel, whose values range from 0
    /// to 765. (765 is the sum of the maximum value of each color channel, assuming a maximum value
    /// of 255 for each of the RGB color channels)
    /// @param outPixelEnergy Output parameter where the calculated pixel energy will be stored.The
    /// edge pixel energy has already been calculated and initialized to its default value.
    void calculatePixelEnergy(const IArray2D<SeamCarverData::PixelColorType>& matrix,
                              IArray2D<SeamCarverData::PixelEnergyType>& outPixelEnergy) const
        noexcept;

  private:
    /// @brief calculate energy for every row, but starting column can be changed. Recommended to
    /// call this with two threads. One to compute odd columns and another to compute even columns.
    /// For odd columns, startingColumn should be set to 1. For even columns, startingColumn should
    /// be set to 2 (0 is the edge).
    /// @param
    /// @param
    /// @param
    void calculateEnergyForEveryOtherColumn(
        const IArray2D<SeamCarverData::PixelColorType>& matrix,
        IArray2D<SeamCarverData::PixelEnergyType>& outPixelEnergy, size_t startingColumn) const
        noexcept;
};

}  // namespace seamcarver
