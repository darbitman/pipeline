#include "gtest/gtest.h"

#include <memory>
#include <queue>
#include <vector>

#include "PipelineMessageBase.hpp"
#include "PipelineIdentifiers.hpp"
#include "PipelineQueueManager.hpp"
#include "SharedContainer.hpp"

using std::greater;
using std::make_unique;
using std::move;
using std::priority_queue;
using std::unique_ptr;
using std::vector;

namespace pipeline
{
class PipelineQueueManagerTest : public ::testing::Test
{
  protected:
    PipelineQueueManager manager;
};

TEST_F(PipelineQueueManagerTest, InvalidQueue)
{
    try
    {
        auto queueId = manager.createNewQueue(ComponentLinkType::QUEUE_TYPE_UNKNOWN);
    }
    catch (std::invalid_argument& e)
    {
        EXPECT_EQ(manager.getNumberOfQueues(), 0);
    }
}

TEST_F(PipelineQueueManagerTest, CreateFifoQueue)
{
    try
    {
        auto queueId = manager.createNewQueue(ComponentLinkType::QUEUE_TYPE_FIFO);

        EXPECT_GE(queueId, 0);

        EXPECT_EQ(manager.getNumberOfQueues(), 1);

        auto pQueue = manager.getQueue(queueId);

        EXPECT_NE(pQueue, nullptr);

        auto pInvalidQueue = manager.getQueue(0);

        EXPECT_EQ(pInvalidQueue, nullptr);

        try
        {
            manager.deleteQueue(0);

            EXPECT_EQ(manager.getNumberOfQueues(), 1);
        }
        catch (std::invalid_argument& e)
        {
            // TODO
        }

        try
        {
            manager.deleteQueue(queueId);

            EXPECT_EQ(manager.getNumberOfQueues(), 0);
        }
        catch (std::invalid_argument& e)
        {
            // TODO
        }
    }
    catch (std::invalid_argument& e)
    {
        EXPECT_EQ(manager.getNumberOfQueues(), 0);
    }
}

TEST_F(PipelineQueueManagerTest, CreateMinPq)
{
    try
    {
        auto queueId = manager.createNewQueue(ComponentLinkType::QUEUE_TYPE_MIN_PQ);

        EXPECT_GE(queueId, 0);

        EXPECT_EQ(manager.getNumberOfQueues(), 1);

        auto pQueue = manager.getQueue(queueId);

        EXPECT_NE(pQueue, nullptr);

        auto pInvalidQueue = manager.getQueue(0);

        EXPECT_EQ(pInvalidQueue, nullptr);

        try
        {
            manager.deleteQueue(0);

            EXPECT_EQ(manager.getNumberOfQueues(), 1);
        }
        catch (std::invalid_argument& e)
        {
            // TODO
        }

        try
        {
            manager.deleteQueue(queueId);

            EXPECT_EQ(manager.getNumberOfQueues(), 0);
        }
        catch (std::invalid_argument& e)
        {
            // TODO
        }
    }
    catch (std::invalid_argument& e)
    {
        EXPECT_EQ(manager.getNumberOfQueues(), 0);
    }
}

}  // namespace pipeline
