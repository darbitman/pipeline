#include "PixelEnergyCalculator.hpp"

#include <thread>

namespace seamcarver
{
void PixelEnergyCalculator::calculatePixelEnergy(
    const IArray2D<SeamCarverData::PixelColorType>& matrix,
    IArray2D<SeamCarverData::PixelEnergyType>& outPixelEnergy) const noexcept
{
    // compute for odd columns
    // compute odd columns
    // calculateEnergyForEveryOtherColumn(matrix, outPixelEnergy, 1);
    // calculateEnergyForEveryOtherColumn(matrix, outPixelEnergy, 2);

    std::thread thread1 = std::thread(&PixelEnergyCalculator::calculateEnergyForEveryOtherColumn,
                                      this, std::ref(matrix), std::ref(outPixelEnergy), 1);
    std::thread thread2 = std::thread(&PixelEnergyCalculator::calculateEnergyForEveryOtherColumn,
                                      this, std::ref(matrix), std::ref(outPixelEnergy), 2);
    thread1.join();
    thread2.join();
}

void PixelEnergyCalculator::calculateEnergyForEveryOtherColumn(
    const IArray2D<SeamCarverData::PixelColorType>& matrix,
    IArray2D<SeamCarverData::PixelEnergyType>& outPixelEnergy, size_t startingColumn) const noexcept
{
    // get dimensions
    auto dimensions = matrix.size();

    size_t bottomRow = dimensions.first - 1;
    size_t rightColumn = dimensions.second - 1;

    // Ignore row 0 and bottom row since those are set to a constant energy value (ie edge pixel
    // energy)
    for (size_t row = 1; row < bottomRow; ++row)
    {
        // Ignore column 0 and right most column since those are set to a constant energy value (ie
        // edge pixel energy)
        for (size_t column = startingColumn; column < rightColumn; column += 2)
        {
            // Compute gradient in X and Y directions
            try
            {
                auto deltaX = abs(matrix(row, column + 1) - matrix(row, column - 1));
                auto deltaY = abs(matrix(row + 1, column) - matrix(row - 1, column));

                // Pixel energy is the sum of gradients
                outPixelEnergy(row, column) = deltaX + deltaY;

                auto& be16toh = outPixelEnergy(row, column);
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
