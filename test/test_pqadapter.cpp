#include "gtest/gtest.h"

#include <stdlib.h>
#include <cstdint>
#include <functional>
#include <memory>
#include <queue>

#include "ConstSizePriorityQueue.hpp"
#include "SharedConstSizePQAdapter.hpp"
#include "VerticalSeamCarverData.hpp"

using std::make_shared;
using std::priority_queue;
using std::shared_ptr;
using std::vector;
using namespace sc;

namespace seamcarver_test
{
namespace
{
TEST(PQAdapter, Initialize)
{
    size_t pqCapacity = 150;
    shared_ptr<ConstSizePriorityQueue<int32_t>> pConstSizeMinPQ =
        make_shared<ConstSizePriorityQueue<int32_t>>(pqCapacity);

    SharedConstSizePQAdapter<int32_t> adapter(pConstSizeMinPQ);

    adapter.push(100);
    adapter.push(125);
    adapter.push(12);

    EXPECT_EQ(adapter.getNext(), 12);
}

TEST(PQAdapter, MinOrientedPQ)
{
    class ComparePointerData
    {
    public:
        bool operator()(shared_ptr<VerticalSeamCarverData> p1,
                        shared_ptr<VerticalSeamCarverData> p2)
        {
            return p1->getFrameNumber() < p2->getFrameNumber();
        }
    };

    size_t pqCapacity = 150;

    shared_ptr<ConstSizePriorityQueue<shared_ptr<VerticalSeamCarverData>, ComparePointerData>> pPq =
        make_shared<ConstSizePriorityQueue<shared_ptr<VerticalSeamCarverData>, ComparePointerData>>(
            pqCapacity);

    EXPECT_EQ(pPq->capacity(), pqCapacity);

    SharedConstSizePQAdapter<shared_ptr<VerticalSeamCarverData>, ComparePointerData> pqAdapter(pPq);

    EXPECT_EQ(pqAdapter.size(), pPq->size());

    // fill in a general PQ, then place into a vector to use for comparison later
    priority_queue<uint32_t, vector<uint32_t>, std::greater<uint32_t>> randomFrameNumbers;
    vector<uint32_t> sortedFrameNumbers;

    // generate random numbers and place them into the pq under test and the general pq from std
    for (int32_t i = 0; i < 10; ++i)
    {
        shared_ptr<VerticalSeamCarverData> pData = make_shared<VerticalSeamCarverData>();
        uint32_t randomNumber = (uint32_t)(rand() % 50);
        pData->setFrameNumber(randomNumber);
        randomFrameNumbers.push(randomNumber);
        pqAdapter.push(pData);
    }

    // the vector will have the numbers sorted that are from the general pq
    while (!randomFrameNumbers.empty())
    {
        sortedFrameNumbers.push_back(randomFrameNumbers.top());
        randomFrameNumbers.pop();
    }

    // compare the sorted vector to the pq under test
    vector<uint32_t>::iterator iter = sortedFrameNumbers.begin();
    while (!pqAdapter.empty())
    {
        ASSERT_EQ(*iter, pqAdapter.getNext()->getFrameNumber());
        pqAdapter.removeNext();
        ++iter;
    }
}
}  // namespace
}  // namespace seamcarver_test
