#include "gtest/gtest.h"

#include <stdlib.h>
#include <cstdint>
#include <functional>
#include <memory>
#include <queue>

#include "ConstSizePriorityQueue.hpp"
#include "SharedConstSizePQAdapter.hpp"

using std::greater;
using std::less;
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
        pPQueue_ = make_shared<ConstSizePriorityQueue<int32_t, less<int32_t>>>(pqCapacity_);

        pAdapter_ = make_shared<SharedConstSizePQAdapter<int32_t, less<int32_t>>>(pPQueue_);
    }

    shared_ptr<ConstSizePriorityQueue<int32_t, less<int32_t>>> pPQueue_;

    shared_ptr<SharedConstSizePQAdapter<int32_t, less<int32_t>>> pAdapter_;

    const size_t pqCapacity_;
};

TEST_F(PqAdapterTest, EmptyOnCreation)
{
    EXPECT_EQ(pAdapter_->empty(), true);

    EXPECT_EQ(pAdapter_->size(), 0);

    EXPECT_EQ(pPQueue_->empty(), true);

    EXPECT_EQ(pPQueue_->size(), 0);
}

TEST_F(PqAdapterTest, MinOrientedPq)
{
    priority_queue<int32_t, vector<int32_t>, greater<int32_t>> randomFrameNumbers;

    // generate random numbers and place them into the pq under test and the general pq from std
    for (int32_t i = 0; i < 10; ++i)
    {
        uint32_t randomNumber = (uint32_t)(rand() % 50);
        randomFrameNumbers.push(randomNumber);
        pAdapter_->push(randomNumber);
    }

    while (!pAdapter_->empty())
    {
        EXPECT_EQ(pAdapter_->front(), randomFrameNumbers.top());
        pAdapter_->pop();
        randomFrameNumbers.pop();
    }
}

}  // namespace sc
