#include "SeamFinderStage.hpp"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SeamCarverStageFactoryRegistration.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace sc
{
SeamFinderStage::SeamFinderStage(std::shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : BasePipelineStage(EPipelineStageId::STAGE_2, EPipelineQueueType::QUEUE_TYPE_FIFO,
                        pSenderReceiver)
{
}

SeamFinderStage::~SeamFinderStage() {}

void SeamFinderStage::initialize() { BasePipelineStage::initialize(); }

void SeamFinderStage::runStage() { BasePipelineStage::runStage(); }

void SeamFinderStage::stopStage() { BasePipelineStage::stopStage(); }

bool SeamFinderStage::isInitialized() const { return BasePipelineStage::isInitialized(); }

bool SeamFinderStage::isRunning() const { return BasePipelineStage::isRunning(); }

void SeamFinderStage::processData(shared_ptr<BasePipelineData> pData)
{
    auto pSeamCarverData = (VerticalSeamCarverData*)(pData.get());
}

// void SeamFinderStage::findSeams(VerticalSeamCarverData* data)
// {
//     // initial cumulative energy path has been calculated in the previous step

//     // declare/initialize variables used in currentSeam discovery when looking for the least
//     // cumulative energy column in the bottom row
//     // flag to indicate whether current seam discovery iteration needs to be restarted
//     bool bRestartSeamDiscovery = false;

//     // declare variables to keep track of columns when traversing up the seam
//     size_t prevColumn = 0;
//     size_t currentColumn = 0;

//     /*** RUN SEAM DISCOVERY ***/
//     for (int32_t n = 0; n < (int32_t)data->numSeamsToRemove_; n++)
//     {
//         // initialize total energy to +INF and run linear search for a pixel of least
//         // cumulative energy (if one exists) in the bottom row
//         double minTotalEnergy = data->posInf_;
//         int32_t minTotalEnergyColumn = -1;
//         for (size_t column = 0; column < data->numColumns_; column++)
//         {
//             if (!data->markedPixels[data->bottomRow_][column] &&
//                 data->totalEnergyTo[data->bottomRow_][column] < minTotalEnergy)
//             {
//                 minTotalEnergy = data->totalEnergyTo[data->bottomRow_][column];
//                 minTotalEnergyColumn = column;
//             }
//         }

//         // all pixels in bottom row are unreachable due to +INF cumulative energy to all of
//         // them therefore need to recalculate cumulative energies
//         if (minTotalEnergyColumn == -1)
//         {
//             // decrement iterator since this seam will need to be restarted after
//             // recalculating the cumulative energy
//             n--;
//             // TODO implement runCumulativePathEnergyCalculation(data);

//             // skip over the seam traversal algorithm below and restart algorithm to
//             // rediscover the seam for this iteration
//             continue;
//         }

//         // save last column as part of currentSeam that will be checked whether it can fully
//         // reach the top row
//         data->currentSeam[data->bottomRow_] = minTotalEnergyColumn;

//         // initialize column variables
//         prevColumn = minTotalEnergyColumn;
//         currentColumn = prevColumn;

//         // run seam traversal starting at bottom row to find all the pixels in the seam
//         for (int32_t row = data->bottomRow_ - 1; row >= 0; row--)
//         {
//             // using the below pixel's row and column, extract the column of the pixel in
//             // the current row
//             currentColumn = data->columnTo[(size_t)row + 1][prevColumn];

//             // check if the current pixel of the current seam has been used part of another
//             // seam
//             if (data->markedPixels[(size_t)row][currentColumn])
//             {
//                 // mark the starting pixel in bottom row as having +INF cumulative energy so
//                 // it will not be chosen again
//                 data->totalEnergyTo[data->bottomRow_][minTotalEnergyColumn] = data->posInf_;

//                 // decrement seam iterator since this seam is invalid and this iteration
//                 // will need to be restarted
//                 n--;

//                 // set to indicate that the outer for loop will need to be restarted for
//                 // this seam iteration
//                 bRestartSeamDiscovery = true;
//                 break;
//             }

//             // save the column of the pixel in the current row
//             data->currentSeam[(size_t)row] = currentColumn;

//             // save current column to be used for the next iteration of the loop
//             prevColumn = currentColumn;
//         }

//         if (bRestartSeamDiscovery)
//         {
//             bRestartSeamDiscovery = false;
//             continue;
//         }
//         else
//         {
//             // copy current seam into the discovered seams and mark appropriate pixels
//             for (size_t row = 0; row < data->numRows_; row++)
//             {
//                 currentColumn = data->currentSeam[row];
//                 data->discoveredSeams[row].push(currentColumn);
//                 data->markedPixels[row][currentColumn] = true;
//             }
//         }
//     }  // for (int32_t n = 0; n < (int32_t)numSeamsToRemove_; n++)
// }

namespace
{
SeamCarverStageFactoryRegistration registerstage(
    EPipelineStageId::STAGE_2, [](std::shared_ptr<PipelineSenderReceiver> pSenderReceiver) {
        return dynamic_pointer_cast<IPipelineStage>(
            make_shared<SeamFinderStage>(pSenderReceiver));
    });
}  // namespace

}  // namespace sc
