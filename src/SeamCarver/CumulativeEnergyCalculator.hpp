#pragma once

#include "IArray2D.hpp"
#include "SeamCarverData.hpp"

namespace seamcarver
{
class CumulativeEnergyCalculator
{
  public:
    /// @brief
    /// @param
    /// @param
    /// @param
    /// @param
    void calculatePixelEnergy(const IArray2D<SeamCarverData::PixelEnergyType>& pixelEnergy,
                              IArray2D<SeamCarverData::PixelEnergyType>& cumulativeEnergyToPixel,
                              IArray2D<SeamCarverData::PixelColumnType>& columnToPixel,
                              IArray2D<bool>& markedPixels) const noexcept;
};

}  // namespace seamcarver
