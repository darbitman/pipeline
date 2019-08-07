#include "gtest/gtest.h"

#include <memory>
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
        fifo_queue_id_ = manager.createNewQueue(PipelineQueueTypes::QUEUE_TYPE_FIFO);
        pq_queue_id_ = manager.createNewQueue(PipelineQueueTypes::QUEUE_TYPE_MIN_PQ);
    }

    int32_t fifo_queue_id_;

    int32_t pq_queue_id_;

    PipelineQueueManager manager;
};

TEST_F(PipelineQueueManagerTest, DoesManagerIntializeQueues)
{
    auto q1 = manager.getQueue(fifo_queue_id_);
    auto q2 = manager.getQueue(pq_queue_id_);
    auto q3 = manager.getQueue(19);

    ASSERT_NE(q1, nullptr);
    ASSERT_NE(q2, nullptr);
    ASSERT_EQ(q3, nullptr);

    EXPECT_EQ(q1->empty(), true);
    EXPECT_EQ(q2->empty(), true);
}

TEST_F(PipelineQueueManagerTest, VerifyMinOrientedPQ)
{
    auto q2 = manager.getQueue(pq_queue_id_);

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
