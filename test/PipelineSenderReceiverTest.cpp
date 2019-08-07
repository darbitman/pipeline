#include "gtest/gtest.h"

#include <memory>

#include "PipelineDataMessage.hpp"
#include "PipelineQueueTypes.hpp"
#include "PipelineSenderReceiver.hpp"
#include "ShutdownMessage.hpp"

using std::make_shared;
using std::shared_ptr;

namespace sc
{
class PipelineSenderReceiverTest : public ::testing::Test
{
  protected:
    virtual void SetUp() override
    {
        senderReceiver.initialize();

        senderReceiver.registerNewStage(PipelineStage::STAGE_0,
                                        PipelineQueueTypes::QUEUE_TYPE_FIFO);
    }

    static PipelineSenderReceiver senderReceiver;
};

PipelineSenderReceiver PipelineSenderReceiverTest::senderReceiver;

TEST_F(PipelineSenderReceiverTest, CheckSendAndReceive)
{
    auto destination = PipelineStage::STAGE_0;
    shared_ptr<BasePipelineMessage> pMessage =
        make_shared<PipelineDataMessage>(destination, nullptr);

    ASSERT_EQ(senderReceiver.send(pMessage), true);

    auto pReceivedMessage = senderReceiver.receive(PipelineStage::STAGE_0);

    EXPECT_EQ(pMessage, pReceivedMessage);
}

TEST_F(PipelineSenderReceiverTest, ShutdownThread)
{
    EXPECT_EQ(senderReceiver.isShutdown(), false);

    auto destination = PipelineStage::MESSAGE_ROUTER;
    shared_ptr<BasePipelineMessage> pMessage =
        make_shared<ShutdownMessage>(destination);

    ASSERT_EQ(senderReceiver.send(pMessage), true);

    while (senderReceiver.isShutdown() == false)
        ;

    EXPECT_EQ(senderReceiver.isShutdown(), true);
}

}  // namespace sc
