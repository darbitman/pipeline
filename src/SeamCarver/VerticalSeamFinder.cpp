#include "VerticalSeamFinder.hpp"

namespace seamcarver
{
void VerticalSeamFinder::findVerticalSeams(int32_t numberOfSeamsToFind,
                                           const IArray2D<PixelColumnType>& cumulativeEnergyToPixel,
                                           IArray2D<bool>& markedPixels) const noexcept
{
    // flag to indicate whether current seam discovery iteration needs to be restarted
    bool bRestartSeamDiscovery = false;

    auto [numRows, numColumns] = cumulativeEnergyToPixel.size();

    PixelColumnType previousColumn = 0;
    PixelColumnType currentColumn = 0;

    for (size_t seamNumber = 0; seamNumber < numberOfSeamsToFind; ++seamNumber)
    {
        auto [numRows, numColumns] = cumulativeEnergyToPixel.size();

        PixelEnergyType minTotalEnergy = MAXIMUM_ENERGY;
        PixelColumnType minTotalEnergyColumn = -1;

        for (PixelColumnType column = 0; column < numColumns; ++column)
        {
            //
        }
    }
}

}  // namespace seamcarver
