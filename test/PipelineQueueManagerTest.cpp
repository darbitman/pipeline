#include "gtest/gtest.h"

#include <queue>
#include <vector>

#include "BasePipelineMessage.hpp"
#include "PipelineQueueManager.hpp"
#include "PipelineQueueTypes.hpp"
#include "VerticalSeamCarverData.hpp"

using std::greater;
using std::make_shared;
using std::priority_queue;
using std::shared_ptr;
using std::vector;

namespace sc
{
class PipelineQueueManagerTest : public ::testing::Test
{
  protected:
    virtual void SetUp() override
    {
        queue_ids.push_back(0);
        queue_ids.push_back(1);

        queue_types.push_back(PipelineQueueTypes::QUEUE_TYPE_FIFO);
        queue_types.push_back(PipelineQueueTypes::QUEUE_TYPE_MIN_PQ);

        manager.initialize(queue_ids, queue_types);
    }

    PipelineQueueManager manager;

  private:
    vector<int32_t> queue_ids;

    vector<int32_t> queue_types;
};

TEST_F(PipelineQueueManagerTest, DoesManagerIntializeQueues)
{
    ASSERT_EQ(manager.isInitialized(), true);

    auto q1 = manager.getQueue(0);
    auto q2 = manager.getQueue(1);
    auto q3 = manager.getQueue(2);

    ASSERT_NE(q1, nullptr);
    ASSERT_NE(q2, nullptr);
    ASSERT_EQ(q3, nullptr);

    EXPECT_EQ(q1->empty(), true);
    EXPECT_EQ(q2->empty(), true);
}

TEST_F(PipelineQueueManagerTest, VerifyMinOrientedPQ)
{
    auto q2 = manager.getQueue(1);

    // system implementation of a min oriented PQ
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t>> randomFrameNumbers;

    // generate random numbers
    // fill in a general PQ and the queue returned by the queue manager with random numbers
    for (int32_t i = 0; i < 10; ++i)
    {
        auto stage = PipelineStage::STAGE_0;

        auto pNewMessage = make_shared<PipelineDataMessage>(stage, nullptr);

        uint32_t randomNumber = (uint32_t)(rand() % 50);
        pNewMessage->setMessageNumber(randomNumber);

        randomFrameNumbers.push(randomNumber);
        q2->push(pNewMessage);
    }

    // both PQs must return the same number
    while (!q2->empty())
    {
        EXPECT_EQ(q2->front()->getMessageNumber(), randomFrameNumbers.top());
        q2->pop();
        randomFrameNumbers.pop();
    }
}
}  // namespace sc
