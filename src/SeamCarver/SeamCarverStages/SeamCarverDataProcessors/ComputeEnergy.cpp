#include "ComputeEnergy.hpp"

#include <memory>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

#include "VerticalSeamCarverData.hpp"

using cv::Mat;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::ref;
using std::shared_ptr;
using std::thread;
using std::vector;

namespace sc
{
ComputeEnergy::ComputeEnergy() {}

ComputeEnergy::~ComputeEnergy() {}

void ComputeEnergy::runSeamCarverProcessor(shared_ptr<VerticalSeamCarverData> pData)
{
    // TODO

    // set local data members for the computation
    numRows_ = pData->getNumberOfRows();
    numColumns_ = pData->getNumberOfColumns();
    bottomRow_ = pData->getBottomRowIndex();
    rightColumn_ = pData->getRightColumnIndex();
    numColorChannels_ = pData->getNumberOfColorChannels();
    marginEnergy_ = pData->getEdgePixelEnergy();

    calculatePixelEnergy(pData->getSavedImage(), )
}

void ComputeEnergy::calculatePixelEnergy(const shared_ptr<const Mat>& image,
                                         vector<vector<double>>& outPixelEnergy)
{
    // if more columns, split calculation into 2 operations to calculate for every row
    if (numColumns_ >= numRows_)
    {
        thread thread1(&ComputeEnergy::calculatePixelEnergyForEveryRow, this, ref(image),
                       ref(outPixelEnergy), true);
        thread thread2(&ComputeEnergy::calculatePixelEnergyForEveryRow, this, ref(image),
                       ref(outPixelEnergy), false);
        while (!thread1.joinable())
            ;
        thread1.join();
        while (!thread2.joinable())
            ;
        thread2.join();
    }
    // otherwise, if more rows, split calculation into 2 operations to calculate for every column
    else
    {
        thread thread1(&ComputeEnergy::calculatePixelEnergyForEveryColumn, this, ref(image),
                       ref(outPixelEnergy), true);
        thread thread2(&ComputeEnergy::calculatePixelEnergyForEveryColumn, this, ref(image),
                       ref(outPixelEnergy), false);
        while (!thread1.joinable())
            ;
        thread1.join();
        while (!thread2.joinable())
            ;
        thread2.join();
    }
}

void ComputeEnergy::calculatePixelEnergyForEveryRow(const shared_ptr<const Mat>& image,
                                                    vector<vector<double>>& outPixelEnergy,
                                                    bool bDoOddColumns)
{
    // TODO
}

void ComputeEnergy::calculatePixelEnergyForEveryColumn(const shared_ptr<const Mat>& image,
                                                       vector<vector<double>>& outPixelEnergy,
                                                       bool bDoOddRows)
{
    // TODO
}

}  // namespace sc
