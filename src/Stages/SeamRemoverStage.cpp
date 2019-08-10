#include "SeamRemoverStage.hpp"

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
SeamRemoverStage::SeamRemoverStage(shared_ptr<PipelineSenderReceiver> pSenderReceiver)
    : BasePipelineStage(EPipelineStageId::STAGE_3, EPipelineQueueType::QUEUE_TYPE_FIFO,
                        pSenderReceiver)
{
}

SeamRemoverStage::~SeamRemoverStage() {}

void SeamRemoverStage::initialize() { BasePipelineStage::initialize(); }

void SeamRemoverStage::runStage() { BasePipelineStage::runStage(); }

void SeamRemoverStage::stopStage() { BasePipelineStage::stopStage(); }

bool SeamRemoverStage::isInitialized() const { return BasePipelineStage::isInitialized(); }

bool SeamRemoverStage::isRunning() const { return BasePipelineStage::isRunning(); }

void SeamRemoverStage::processData(shared_ptr<BasePipelineData> pData)
{
    auto pSeamCarverData = (VerticalSeamCarverData*)(pData.get());
}

// void SeamRemoverStage::removeSeams(VerticalSeamCarverData* data)
// {
//     // each row of seams stores an ordered queue of pixels to remove in that row
//     //   starting with the min number column
//     // each time a new column is encountered, move the pixels to the right of it
//     //   (up until the next column number) to the left by the number of pixels already
//     //   removed

//     size_t colToRemove = 0;
//     size_t numSeamsRemoved = 0;
//     /*** REMOVE PIXELS FOR EVERY ROW ***/
//     for (size_t row = 0; row < data->numRows_; row++)
//     {
//         // seamRecalculationCount the number of seams to the left of the current pixel
//         //   to indicate how many spaces to move pixels that aren't being removed to the
//         //   left
//         numSeamsRemoved = 0;
//         // loop through all pixels to remove in current row
//         while (!data->discoveredSeams[row].empty())
//         {
//             numSeamsRemoved++;
//             // column location of pixel to remove in row
//             colToRemove = data->discoveredSeams[row].top();
//             data->discoveredSeams[row].pop();

//             // mark right endpoint/next pixel column
//             size_t rightColBorder =
//                 (data->discoveredSeams[row].empty() ? data->numColumns_
//                                                     : data->discoveredSeams[row].top());
//             // starting at the column to the right of the column to remove,
//             //      move the pixel to the left, by the number of seams to the left of the
//             //      pixel, until the right end point which is either the last column or the
//             //      next column to remove whichever comes first
//             for (size_t column = colToRemove + 1; column < rightColBorder; column++)
//             {
//                 for (size_t j = 0; j < data->numColorChannels_; j++)
//                 {
//                     data->bgr[j].at<unsigned char>(row, column - numSeamsRemoved) =
//                         data->bgr[j].at<unsigned char>(row, column);
//                 }
//             }
//         }
//     }

//     /*** SHRINK IMAGE SINCE THE IMPORTANT SEAMS WERE SHIFTED LEFT ***/
//     for (size_t channel = 0; channel < data->numColorChannels_; channel++)
//     {
//         data->bgr[channel] = data->bgr[channel].colRange(0, data->numColumns_ - numSeamsRemoved);
//     }
// }

namespace
{
SeamCarverStageFactoryRegistration registerstage(
    EPipelineStageId::STAGE_3, [](shared_ptr<PipelineSenderReceiver> pSenderReceiver) {
        return dynamic_pointer_cast<IPipelineStage>(make_shared<SeamRemoverStage>(pSenderReceiver));
    });
}

}  // namespace sc
