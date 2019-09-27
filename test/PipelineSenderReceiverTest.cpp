#include "gtest/gtest.h"

#include <memory>

#include "PipelineCommon.hpp"
#include "PipelineDataMessage.hpp"
#include "PipelineSenderReceiver.hpp"
#include "ShutdownMessage.hpp"

using std::make_unique;
using std::unique_ptr;

namespace sc
{
class PipelineSenderReceiverTest : public ::testing::Test
{
  protected:
    virtual void SetUp() override
    {
        senderReceiver.initialize();

        senderReceiver.registerComponent(EComponentId::STAGE_0,
                                        EComponentLinkType::QUEUE_TYPE_FIFO);
    }

    static PipelineSenderReceiver senderReceiver;
};

PipelineSenderReceiver PipelineSenderReceiverTest::senderReceiver;

TEST_F(PipelineSenderReceiverTest, CheckSendAndReceive)
{
    auto source = EComponentId::INTERFACE_STAGE;
    auto destination = EComponentId::STAGE_0;
    unique_ptr<BasePipelineData> pEmptyData;
    unique_ptr<BasePipelineMessage> pMessage =
        make_unique<PipelineDataMessage>(source, destination, 0, pEmptyData);

    const BasePipelineMessage* const savedPtr = pMessage.get();

    ASSERT_EQ(senderReceiver.send(pMessage), true);

    auto pReceivedMessage = senderReceiver.receive(EComponentId::STAGE_0);

    EXPECT_EQ(savedPtr, pReceivedMessage.get());
}

TEST_F(PipelineSenderReceiverTest, ShutdownThread)
{
    EXPECT_EQ(senderReceiver.isShutdown(), false);

    unique_ptr<BasePipelineMessage> pMessage =
        make_unique<ShutdownMessage>(EComponentId::MESSAGE_ROUTER, EComponentId::MESSAGE_ROUTER, 0);

    ASSERT_EQ(senderReceiver.send(pMessage), true);

    while (senderReceiver.isShutdown() == false)
        ;

    EXPECT_EQ(senderReceiver.isShutdown(), true);
}

}  // namespace sc
