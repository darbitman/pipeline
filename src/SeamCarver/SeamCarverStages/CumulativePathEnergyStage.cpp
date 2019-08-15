#include "CumulativePathEnergyStage.hpp"

#include <memory>
#include <thread>
#include <vector>

#include "PipelineCommon.hpp"
#include "PipelineSenderReceiver.hpp"
#include "VerticalSeamCarverData.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace sc
{
CumulativePathEnergyStage::CumulativePathEnergyStage(
    shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : BasePipelineStage(EPipelineStageId::STAGE_1, EPipelineQueueType::QUEUE_TYPE_FIFO,
                        pSenderReceiver)
{
}

CumulativePathEnergyStage::~CumulativePathEnergyStage() {}

void CumulativePathEnergyStage::initialize() { BasePipelineStage::initialize(); }

void CumulativePathEnergyStage::runStage() { BasePipelineStage::runStage(); }

void CumulativePathEnergyStage::stopStage() { BasePipelineStage::stopStage(); }

bool CumulativePathEnergyStage::isInitialized() const { return BasePipelineStage::isInitialized(); }

bool CumulativePathEnergyStage::isRunning() const { return BasePipelineStage::isRunning(); }

void CumulativePathEnergyStage::processData(shared_ptr<BasePipelineData> pData)
{
    auto pSeamCarverData = (VerticalSeamCarverData*)(pData.get());
}

// void CumulativePathEnergyStage::calculateCumulativePathEnergy(VerticalSeamCarverData* data)
// {
//     // initialize top row
//     for (size_t column = 0; column < data->numColumns_; column++)
//     {
//         // if previously markedPixels, set its energy to +INF
//         if (data->markedPixels[0][column])
//         {
//             data->totalEnergyTo[0][column] = data->posInf_;
//         }
//         else
//         {
//             data->totalEnergyTo[0][column] = data->marginEnergy_;
//         }
//         data->columnTo[0][column] = -1;
//     }

//     // cache the total energy to the pixels up/left, directly above, and up/right
//     //   instead of accessing memory for the same pixels
//     // shift energy values to the left and access memory only once
//     // SHIFT OPERATION:
//     //   left/above <== directly above
//     //   directly above <== right/above
//     //   right/above = access new memory
//     double energyUpLeft = data->posInf_;
//     double energyUp = data->posInf_;
//     double energyUpRight = data->posInf_;

//     double minEnergy = data->posInf_;
//     int32_t minEnergyColumn = -1;

//     for (size_t row = 1; row < data->numRows_; row++)
//     {
//         energyUpLeft = data->posInf_;
//         energyUp = data->totalEnergyTo[row - 1][0];
//         energyUpRight = data->numColumns_ > 1 ? data->totalEnergyTo[row - 1][1] : data->posInf_;

//         bool markedUpLeft = true;
//         bool markedUp = data->markedPixels[row - 1][0];
//         bool markedUpRight = data->numColumns_ > 1 ? data->markedPixels[row - 1][1] : true;

//         // find minimum energy path from previous row to every pixel in the current row
//         for (size_t column = 0; column < data->numColumns_; column++)
//         {
//             // initialize min energy to +INF and initialize the previous column to -1
//             //   to set error state
//             minEnergy = data->posInf_;
//             minEnergyColumn = -1;

//             // save some cycles by not doing any comparisons if the current pixel has been
//             //      previously marked
//             if (!data->markedPixels[row][column])
//             {
//                 // check above
//                 if (!markedUp && energyUp < minEnergy)
//                 {
//                     minEnergy = energyUp;
//                     minEnergyColumn = column;
//                 }

//                 // check if right/above is min
//                 if (column < data->numColumns_ - 1)
//                 {
//                     if (!markedUpRight && energyUpRight < minEnergy)
//                     {
//                         minEnergy = energyUpRight;
//                         minEnergyColumn = column + 1;
//                     }
//                 }

//                 // check if left/above is min
//                 if (column > 0)
//                 {
//                     if (!markedUpLeft && energyUpLeft < minEnergy)
//                     {
//                         minEnergy = energyUpLeft;
//                         minEnergyColumn = column - 1;
//                     }
//                 }
//             }

//             // shift energy to the left
//             energyUpLeft = energyUp;
//             markedUpLeft = markedUp;
//             energyUp = energyUpRight;
//             markedUp = markedUpRight;

//             // get markedPixels and totalEnergyTo data for pixels right/above
//             if (data->numColumns_ > 1 && column < data->numColumns_ - 2)
//             {
//                 energyUpRight = data->totalEnergyTo[row - 1][column + 2];
//                 markedUpRight = data->markedPixels[row - 1][column + 2];
//             }

//             // assign cumulative energy to current pixel and save the column of the parent pixel
//             if (minEnergyColumn == -1)
//             {
//                 // current pixel is unreachable from parent pixels since they are all
//                 // markedPixels
//                 //   OR current pixel already markedPixels
//                 // set energy to reach current pixel to +INF
//                 data->totalEnergyTo[row][column] = data->posInf_;
//             }
//             else
//             {
//                 data->totalEnergyTo[row][column] = minEnergy + data->pixelEnergy[row][column];
//             }
//             data->columnTo[row][column] = minEnergyColumn;
//         }
//     }
// }

}  // namespace sc
