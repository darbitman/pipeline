#include "gtest/gtest.h"

#include <stdlib.h>
#include <functional>
#include <queue>
#include <vector>

#include "PriorityQueue.hpp"

using std::greater;
using std::priority_queue;
using std::vector;

namespace sc
{
class PriorityQueueTest : public ::testing::Test
{
  protected:
    constexpr static size_t initial_capacity_ = 100;

    static sc::PriorityQueue<int32_t> pq;
};

sc::PriorityQueue<int32_t> PriorityQueueTest::pq(PriorityQueueTest::initial_capacity_);

constexpr size_t PriorityQueueTest::initial_capacity_;

TEST_F(PriorityQueueTest, MinOrientedPriorityQueue)
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

TEST_F(PriorityQueueTest, ResetAndMinOrientedPriorityQueue)
{
    // queue should be empty
    EXPECT_EQ(pq.size(), 0);
    EXPECT_EQ(pq.empty(), true);

    // push a few random numbers and then reset
    pq.push(10);
    pq.push(12);
    pq.resetPriorityQueue();
    EXPECT_EQ(pq.size(), 0);
    EXPECT_EQ(pq.empty(), true);

    priority_queue<int32_t, vector<int32_t>, greater<int32_t>> generalPq;

    // generate random numbers and place them into the pq under test and std::priority_queue
    for (int32_t i = 0; i < 25; ++i)
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

}  // namespace sc
