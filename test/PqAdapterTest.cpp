#include "gtest/gtest.h"

#include <stdlib.h>
#include <cstdint>
#include <functional>
#include <memory>
#include <queue>

#include "ConstSizePriorityQueue.hpp"
#include "SharedConstSizePQAdapter.hpp"

using std::greater;
using std::make_shared;
using std::priority_queue;
using std::shared_ptr;
using std::vector;
using namespace sc;

namespace sc
{
class PqAdapterTest : public ::testing::Test
{
  public:
    PqAdapterTest() : pqCapacity_(100) {}

  protected:
    virtual void SetUp()
    {
        pPQueue_ = make_shared<ConstSizePriorityQueue<int32_t, greater<int32_t>>>(pqCapacity_);
    }

    shared_ptr<ConstSizePriorityQueue<int32_t, greater<int32_t>>> pPQueue_;

    const size_t pqCapacity_;
};

TEST_F(PqAdapterTest, EmptyOnCreation)
{
    EXPECT_EQ(pPQueue_->empty(), true);

    EXPECT_EQ(pPQueue_->size(), 0);
}

// TEST(PQAdapter, MinOrientedPQ)
// {
//     class ComparePointerData
//     {
//       public:
//         bool operator()(shared_ptr<VerticalSeamCarverData> p1,
//                         shared_ptr<VerticalSeamCarverData> p2)
//         {
//             return p1->getFrameNumber() < p2->getFrameNumber();
//         }
//     };

//     size_t pqCapacity = 150;

//     shared_ptr<ConstSizePriorityQueue<shared_ptr<VerticalSeamCarverData>, ComparePointerData>>
//     pPq =
//         make_shared<ConstSizePriorityQueue<shared_ptr<VerticalSeamCarverData>,
//         ComparePointerData>>(
//             pqCapacity);

//     EXPECT_EQ(pPq->capacity(), pqCapacity);

//     SharedConstSizePQAdapter<shared_ptr<VerticalSeamCarverData>, ComparePointerData>
//     pqAdapter(pPq);

//     EXPECT_EQ(pqAdapter.size(), pPq->size());

//     // fill in a general PQ, then place into a vector to use for comparison later
//     priority_queue<uint32_t, vector<uint32_t>, std::greater<uint32_t>> randomFrameNumbers;
//     vector<uint32_t> sortedFrameNumbers;

//     // generate random numbers and place them into the pq under test and the general pq from std
//     for (int32_t i = 0; i < 10; ++i)
//     {
//         shared_ptr<VerticalSeamCarverData> pData = make_shared<VerticalSeamCarverData>();
//         uint32_t randomNumber = (uint32_t)(rand() % 50);
//         pData->setFrameNumber(randomNumber);
//         randomFrameNumbers.push(randomNumber);
//         pqAdapter.push(pData);
//     }

//     // the vector will have the numbers sorted that are from the general pq
//     while (!randomFrameNumbers.empty())
//     {
//         sortedFrameNumbers.push_back(randomFrameNumbers.top());
//         randomFrameNumbers.pop();
//     }

//     // compare the sorted vector to the pq under test
//     vector<uint32_t>::iterator iter = sortedFrameNumbers.begin();
//     while (!pqAdapter.empty())
//     {
//         ASSERT_EQ(*iter, pqAdapter.getNext()->getFrameNumber());
//         pqAdapter.removeNext();
//         ++iter;
//     }
// }

}  // namespace sc
