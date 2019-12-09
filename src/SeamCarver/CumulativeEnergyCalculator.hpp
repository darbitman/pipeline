#pragma once

#include "IArray2D.hpp"
#include "SeamCarverData.hpp"

namespace seamcarver
{
class CumulativeEnergyCalculator
{
  public:
    /// @brief Compute vertical cumulative energy to reach each pixel. As a side effect, the column
    /// to reach each pixel is also calculated and stored.
    /// @param pixelEnergy 2D array of individual pixel energy. Must be calculated prior to invoking
    /// this method
    /// @param cumulativeEnergyToPixel Out parameter. 2D array of calculated cumulative energy for
    /// each pixel
    /// @param columnToPixel Out parameter. 2D array of column indices to reach every pixel
    /// @param markedPixels 2D array of pixels that are marked as part of a seam already, so they
    /// can be ignored
    void calculateCumulativePixelEnergy(
        const IArray2D<SeamCarverData::PixelEnergyType>& pixelEnergy,
        IArray2D<SeamCarverData::PixelEnergyType>& cumulativeEnergyToPixel,
        IArray2D<SeamCarverData::PixelColumnType>& columnToPixel,
        IArray2D<bool>& markedPixels) const noexcept;

  private:
    typedef SeamCarverData::PixelColumnType ColumnType;
    typedef SeamCarverData::PixelEnergyType EnergyType;
    typedef int16_t SignedEnergyType;

    /// @brief Update minEnergy and minEnergyColumn to new values without using branches (ie
    /// if/else statements)
    /// @param flag If true, set the minEnergy and minEnergyColumn output parameters to the new
    /// values, else keep the old values for minEnergy and minEnergyColumn
    /// @param minEnergy Output parameter to update
    /// @param newEnergy The new value for minEnergy
    /// @param minEnergyColumn Output parameter to update
    /// @param newColumn The new value for minEnergyColumn
    void TryUpdateMinimumEnergy(bool flag, EnergyType& minEnergy, EnergyType newEnergy,
                                ColumnType& minEnergyColumn, ColumnType newColumn) const noexcept;
};

}  // namespace seamcarver
