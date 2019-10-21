#include "PixelEnergyCalculator.hpp"

#include <thread>

namespace seamcarver
{
void PixelEnergyCalculator::calculatePixelEnergy(
    const IArray2D<SeamCarverData::PixelColorType>& pixelMatrix,
    IArray2D<SeamCarverData::PixelEnergyType>& outPixelEnergy) const noexcept
{
    // calculateEnergyForEveryOtherColumn(pixelMatrix, outPixelEnergy, 1, 1);
    // calculateEnergyForEveryOtherColumn(pixelMatrix, outPixelEnergy, 1, 2);
    // calculateEnergyForEveryOtherColumn(pixelMatrix, outPixelEnergy, 2, 1);
    // calculateEnergyForEveryOtherColumn(pixelMatrix, outPixelEnergy, 2, 2);

    std::thread thread1 = std::thread(&PixelEnergyCalculator::calculateEnergyForEveryOtherColumn,
                                      this, std::ref(pixelMatrix), std::ref(outPixelEnergy), 1, 1);
    std::thread thread2 = std::thread(&PixelEnergyCalculator::calculateEnergyForEveryOtherColumn,
                                      this, std::ref(pixelMatrix), std::ref(outPixelEnergy), 1, 2);
    std::thread thread3 = std::thread(&PixelEnergyCalculator::calculateEnergyForEveryOtherColumn,
                                      this, std::ref(pixelMatrix), std::ref(outPixelEnergy), 2, 1);
    std::thread thread4 = std::thread(&PixelEnergyCalculator::calculateEnergyForEveryOtherColumn,
                                      this, std::ref(pixelMatrix), std::ref(outPixelEnergy), 2, 2);
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
}

void PixelEnergyCalculator::calculateEnergyForEveryOtherColumn(
    const IArray2D<SeamCarverData::PixelColorType>& pixelMatrix,
    IArray2D<SeamCarverData::PixelEnergyType>& outPixelEnergy, size_t startingRow,
    size_t startingColumn) const noexcept
{
    // get dimensions
    auto dimensions = pixelMatrix.size();

    size_t bottomRow = dimensions.first - 1;
    size_t rightColumn = dimensions.second - 1;

    // Ignore row 0 and bottom row since those are set to a constant energy value (ie edge pixel
    // energy)
    for (size_t row = startingRow; row < bottomRow; row += 2)
    {
        // Ignore column 0 and right most column since those are set to a constant energy value (ie
        // edge pixel energy)
        for (size_t column = startingColumn; column < rightColumn; column += 2)
        {
            // Compute gradient in X and Y directions
            try
            {
                SeamCarverData::PixelColorType deltaX = abs(pixelMatrix(row, column + 1) - pixelMatrix(row, column - 1));
                SeamCarverData::PixelColorType deltaY = abs(pixelMatrix(row + 1, column) - pixelMatrix(row - 1, column));

                // Pixel energy is the sum of gradients
                outPixelEnergy(row, column) = deltaX + deltaY;
            }
            catch (const std::out_of_range& e)
            {
                // go to outer loop
                break;
            }
        }
    }
}

}  // namespace seamcarver
