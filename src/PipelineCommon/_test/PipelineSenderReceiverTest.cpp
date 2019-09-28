#include "gtest/gtest.h"

#include <memory>

#include "PipelineDataMessage.hpp"
#include "PipelineIdentifiers.hpp"
#include "PipelineSenderReceiver.hpp"
#include "SharedContainer.hpp"
#include "ShutdownMessage.hpp"

using std::make_unique;
using std::unique_ptr;

namespace pipeline
{
class PipelineSenderReceiverTest : public ::testing::Test
{
  protected:
    virtual void SetUp() override
    {
        senderReceiver.initialize();

        senderReceiver.registerComponent(ComponentId::STAGE_0, ComponentLinkType::QUEUE_TYPE_FIFO);
    }

    static PipelineSenderReceiver senderReceiver;
};

PipelineSenderReceiver PipelineSenderReceiverTest::senderReceiver;

TEST_F(PipelineSenderReceiverTest, CheckSendAndReceive)
{
    auto source = ComponentId::INTERFACE_STAGE;
    auto destination = ComponentId::STAGE_0;
    unique_ptr<BasePipelineData> pEmptyData;
    unique_ptr<BasePipelineMessage> pMessage =
        make_unique<PipelineDataMessage>(source, destination, 0, pEmptyData);

    const BasePipelineMessage* const savedPtr = pMessage.get();

    auto pReceivedMessage = senderReceiver.receiveMessage(ComponentId::STAGE_0);

    EXPECT_EQ(savedPtr, pReceivedMessage.get());
}

TEST_F(PipelineSenderReceiverTest, ShutdownThread)
{
    EXPECT_EQ(senderReceiver.isShutdown(), false);

    unique_ptr<BasePipelineMessage> pMessage =
        make_unique<ShutdownMessage>(ComponentId::MESSAGE_ROUTER, ComponentId::MESSAGE_ROUTER, 0);

    while (senderReceiver.isShutdown() == false)
        ;

    EXPECT_EQ(senderReceiver.isShutdown(), true);
}

}  // namespace pipeline
