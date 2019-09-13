#include "SeamFinder.hpp"

#include <memory>

#include "CumulativePathEnergy.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

namespace sc
{
SeamFinder::SeamFinder() {}

SeamFinder::~SeamFinder() {}

void SeamFinder::runSeamCarverProcessor(BasePipelineData* pData)
{
    auto& data = *static_cast<VerticalSeamCarverData*>(pData);

    // initial cumulative energy path has been calculated in the previous step

    // declare/initialize variables used in currentSeam discovery when looking for the least
    // cumulative energy column in the bottom row
    // flag to indicate whether current seam discovery iteration needs to be restarted
    bool bRestartSeamDiscovery = false;

    // declare variables to keep track of columns when traversing up the seam
    size_t prevColumn = 0;
    size_t currentColumn = 0;

    auto& markedPixels = data.getMarkedPixel2DVector();
    auto& totalEnergyTo = data.getTotalEnergyToPixel2DVector();
    auto& columnTo = data.getPreviousColumnToCurrentPixel2DVector();
    auto& discoveredSeams = data.getDiscoveredSeamsVectorOfPqs();
    auto numRows = data.getNumberOfRows();
    auto numColumns = data.getNumberOfColumns();
    auto bottomRow = data.getBottomRowIndex();
    auto posInf = data.getPositiveInfinity();

    /*** RUN SEAM DISCOVERY ***/
    int64_t numSeamsToRemove{int64_t(data.getNumberOfSeamsToRemove())};
    for (int32_t n = 0; n < numSeamsToRemove; ++n)
    {
        // initialize total energy to +INF and run linear search for a pixel of least
        // cumulative energy (if one exists) in the bottom row
        double minTotalEnergy = data.getPositiveInfinity();
        int32_t minTotalEnergyColumn = -1;
        for (size_t column = 0; column < numColumns; column++)
        {
            if (!markedPixels[bottomRow][column] &&
                totalEnergyTo[bottomRow][column] < minTotalEnergy)
            {
                minTotalEnergy = totalEnergyTo[bottomRow][column];
                minTotalEnergyColumn = column;
            }
        }

        // all pixels in bottom row are unreachable due to +INF cumulative energy to all of
        // them therefore need to recalculate cumulative energies
        if (minTotalEnergyColumn == -1)
        {
            // decrement iterator since this seam will need to be restarted after
            // recalculating the cumulative energy
            --n;
            CumulativePathEnergy::calculateCumulativePathEnergy(&data);

            // skip over the seam traversal algorithm below and restart algorithm to
            // rediscover the seam for this iteration
            continue;
        }

        // save last column as part of currentSeam that will be checked whether it can fully
        // reach the top row
        data.currentSeam[bottomRow] = minTotalEnergyColumn;

        // initialize column variables
        prevColumn = minTotalEnergyColumn;
        currentColumn = prevColumn;

        // run seam traversal starting at bottom row to find all the pixels in the seam
        for (int32_t row = bottomRow - 1; row >= 0; row--)
        {
            // using the below pixel's row and column, extract the column of the pixel in
            // the current row
            currentColumn = columnTo[(size_t)row + 1][prevColumn];

            // check if the current pixel of the current seam has been used part of another
            // seam
            if (markedPixels[(size_t)row][currentColumn])
            {
                // mark the starting pixel in bottom row as having +INF cumulative energyso
                // it will not be chosen again
                totalEnergyTo[bottomRow][minTotalEnergyColumn] = posInf;

                // decrement seam iterator since this seam is invalid and this iteration
                // will need to be restarted
                n--;

                // set to indicate that the outer for loop will need to be restarted for
                // this seam iteration
                bRestartSeamDiscovery = true;
                break;
            }

            // save the column of the pixel in the current row
            data.currentSeam[(size_t)row] = currentColumn;

            // save current column to be used for the next iteration of the loop
            prevColumn = currentColumn;
        }

        if (bRestartSeamDiscovery)
        {
            bRestartSeamDiscovery = false;
            continue;
        }
        else
        {
            // copy current seam into the discovered seams and mark appropriate pixels
            for (size_t row = 0; row < numRows; row++)
            {
                currentColumn = data.currentSeam[row];
                discoveredSeams[row].push(currentColumn);
                markedPixels[row][currentColumn] = true;
            }
        }
    }  // for (int32_t n = 0; n < (int32_t)numSeamsToRemove_; n++)
}

}  // namespace sc
