#include "gtest/gtest.h"

#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>

#include "ConstSizePriorityQueue.hpp"

using std::greater;
using std::priority_queue;
using std::vector;

namespace sc
{
class ConstSizePriorityQueueTest : public ::testing::Test
{
public:
    ConstSizePriorityQueueTest() : pq(initial_capacity_) {}

protected:
    constexpr static size_t initial_capacity_ = 100;
    constexpr static size_t new_capacity_ = 200;

    sc::ConstSizePriorityQueue<int32_t> pq;
};

constexpr size_t ConstSizePriorityQueueTest::initial_capacity_;
constexpr size_t ConstSizePriorityQueueTest::new_capacity_;

TEST_F(ConstSizePriorityQueueTest, InitialCapacity)
{
    EXPECT_EQ(pq.capacity(), this->initial_capacity_);
}

TEST_F(ConstSizePriorityQueueTest, ChangeCapacity)
{
    pq.changeCapacity(new_capacity_);

    EXPECT_EQ(pq.capacity(), new_capacity_);
}

TEST_F(ConstSizePriorityQueueTest, MinOrientedPQ)
{
    priority_queue<int32_t, vector<int32_t>, greater<int32_t>> generalPq;

    // generate random numbers and place them into the pq under test and std::priority_queue
    for (int32_t i = 0; i < 10; ++i)
    {
        uint32_t randomNumber = (uint32_t)(rand() % 50);
        pq.push(randomNumber);
        generalPq.push(randomNumber);
    }

    while (!pq.empty())
    {
        ASSERT_EQ(pq.top(), generalPq.top());
        pq.pop();
        generalPq.pop();
    }
}
} // namespace sc