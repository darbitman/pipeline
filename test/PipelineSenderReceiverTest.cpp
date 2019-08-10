#include "gtest/gtest.h"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
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

        senderReceiver.registerNewStage(EPipelineStageId::STAGE_0,
                                        EPipelineQueueType::QUEUE_TYPE_FIFO);
    }

    static PipelineSenderReceiver senderReceiver;
};

PipelineSenderReceiver PipelineSenderReceiverTest::senderReceiver;

TEST_F(PipelineSenderReceiverTest, CheckSendAndReceive)
{
    auto source = EPipelineStageId::INTERFACE_STAGE;
    auto destination = EPipelineStageId::STAGE_0;
    shared_ptr<BasePipelineMessage> pMessage =
        make_shared<PipelineDataMessage>(source, destination, nullptr);

    ASSERT_EQ(senderReceiver.send(pMessage), true);

    auto pReceivedMessage = senderReceiver.receive(EPipelineStageId::STAGE_0);

    EXPECT_EQ(pMessage, pReceivedMessage);
}

TEST_F(PipelineSenderReceiverTest, ShutdownThread)
{
    EXPECT_EQ(senderReceiver.isShutdown(), false);

    auto destination = EPipelineStageId::MESSAGE_ROUTER;
    shared_ptr<BasePipelineMessage> pMessage = make_shared<ShutdownMessage>(destination);

    ASSERT_EQ(senderReceiver.send(pMessage), true);

    while (senderReceiver.isShutdown() == false)
        ;

    EXPECT_EQ(senderReceiver.isShutdown(), true);
}

}  // namespace sc
