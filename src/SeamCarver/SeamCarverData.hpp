#pragma once

#include <cstdint>

#include "Matrix.hpp"

namespace seamcarver
{
struct SeamCarverData
{
  public:
    using PixelColorType = uint16_t;
    using PixelEnergyType = uint16_t;

    /// @brief This method will reset all the internal matrices to their clean state
    /// This will do the following:
    ///  1. Set edge pixel energy in pixelEnergy_;
    void resetAllData() noexcept;

    static PixelEnergyType getEdgePixelEnergy() noexcept { return edgePixelEnergy_; }

    // Store the B/W image (ie 'single color channel')
    /// This can be the result of combining the color channels
    /// Legal values are [0, 765]
    pipeline::Matrix<PixelColorType> bwPixelData_;

    /// Flag that indicates if a pixel has been marked for removal
    /// These pixels will be ignored when searching for a new seam
    pipeline::Matrix<bool> markedPixels_;

    /// stores the individual energy for a pixel at [r,c]
    pipeline::Matrix<PixelEnergyType> pixelEnergy_;

    /// Stores the cumulative energy to get to pixel at [r,c]
    pipeline::Matrix<PixelEnergyType> cumulativeEnergyToPixel_;

    /// store the column of the pixel in the previous row that is used to get the curernt pixel
    /// for a pixel at [r,c], there are three possible columns in the previous row that could be
    /// stored (c-1), (c), (c+1)
    pipeline::Matrix<int32_t> columnToPixel_;

  private:
    /// Store the energy of a pixel at the edges
    /// 255 * 3 * 2 (Why 3? For 3 color channels) (Why 2? For dx and dy directions)
    static constexpr PixelEnergyType edgePixelEnergy_ = 1530;
};

}  // namespace seamcarver
