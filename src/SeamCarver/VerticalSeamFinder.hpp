#pragma once

#include "IArray2D.hpp"
#include "SeamCarverCommon.hpp"

#include <vector>

namespace seamcarver
{
class VerticalSeamFinder
{
  public:
    /// @brief
    /// @param numberOfSeamsToFind
    /// @param markedPixels
    /// @return uint32_t The number of seams found
    void findVerticalSeams(int32_t numberOfSeamsToFind,
                           const IArray2D<PixelColumnType>& cumulativeEnergyToPixel,
                           IArray2D<bool>& markedPixels) const noexcept;
};

}  // namespace seamcarver
