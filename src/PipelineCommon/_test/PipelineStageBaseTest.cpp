#include "gtest/gtest.h"

#include <memory>
#include <mutex>
#include <queue>

#include "IDataProcessor.hpp"
#include "IMessageRouter.hpp"
#include "PipelineDataMessage.hpp"
#include "PipelineMessageBase.hpp"
#include "PipelineStageBase.hpp"

using std::make_unique;
using std::move;
using std::mutex;
using std::queue;
using std::unique_lock;
using std::unique_ptr;

namespace pipeline
{
class LinkType
{
  public:
    static constexpr uint32_t DEFAULT_LINK_TYPE{1};
};

class Id
{
  public:
    static constexpr uint32_t COMPONENT_UNDER_TEST{1};
    static constexpr uint32_t COMPONENT_THAT_RECEIVES{2};
    static constexpr uint32_t COMPONENT_THAT_SENDS{3};
};

class MockDataProcessor : public IDataProcessor
{
  public:
    virtual ~MockDataProcessor() = default;

    virtual void processData(PipelineDataBase* pData) override
    {
        // Do no processing
    }
};

class MockMessageRouter : public IMessageRouter
{
  public:
    virtual ~MockMessageRouter() = default;

    virtual void registerComponent(uint32_t componentId,
                                   uint32_t componentLinkType) noexcept override
    {
        // Not required for test
    }

    virtual void unregisterComponent(uint32_t componentId) noexcept override
    {
        // Not required for test
    }

    virtual bool isComponentRegistered(uint32_t componentId) const noexcept override
    {
        // Not required for test
        return true;
    }

    virtual void sendMessage(unique_ptr<PipelineMessageBase>& pMessage) noexcept override
    {
        unique_lock<mutex> lock(mtx_);
        switch (pMessage->getDestination())
        {
            case Id::COMPONENT_THAT_RECEIVES:
                inputQueueToReceiver_.push(move(pMessage));
                break;

            case Id::COMPONENT_UNDER_TEST:
                inputQueueToComponentUnderTest_.push(move(pMessage));
                break;

            default:
                break;
        }
    }

    virtual void sendMessage(unique_ptr<PipelineMessageBase>&& pMessage) noexcept override
    {
        sendMessage(pMessage);
    }

    virtual unique_ptr<PipelineMessageBase> receiveMessage(
        uint32_t receivingComponentId) noexcept override
    {
        unique_lock<mutex> lock(mtx_);
        switch (receivingComponentId)
        {
            case Id::COMPONENT_THAT_RECEIVES:
            {
                if (inputQueueToReceiver_.empty())
                {
                    return unique_ptr<PipelineMessageBase>();
                }
                else
                {
                    auto pReceivedMessage = move(inputQueueToReceiver_.front());
                    inputQueueToReceiver_.pop();
                    return pReceivedMessage;
                }
                break;
            }

            case Id::COMPONENT_UNDER_TEST:
            {
                if (inputQueueToComponentUnderTest_.empty())
                {
                    return unique_ptr<PipelineMessageBase>();
                }
                else
                {
                    auto pReceivedMessage = move(inputQueueToComponentUnderTest_.front());
                    inputQueueToComponentUnderTest_.pop();
                    return pReceivedMessage;
                }
                break;
            }

            default:
                break;
        }

        return unique_ptr<PipelineMessageBase>();
    }

    virtual bool canReceive(uint32_t receivingComponentId) const noexcept override
    {
        unique_lock<mutex> lock(mtx_);
        switch (receivingComponentId)
        {
            case Id::COMPONENT_THAT_RECEIVES:
                return !inputQueueToReceiver_.empty();
                break;

            case Id::COMPONENT_UNDER_TEST:
                return !inputQueueToComponentUnderTest_.empty();
                break;

            default:
                return false;
                break;
        }
    }

  private:
    queue<unique_ptr<PipelineMessageBase>> inputQueueToComponentUnderTest_;
    queue<unique_ptr<PipelineMessageBase>> inputQueueToReceiver_;

    mutable mutex mtx_;
};

class PipelineStageBaseTest : public ::testing::Test
{
  public:
    PipelineStageBaseTest()
        : messageRouter_(),
          dataProcessor_(),
          stage_(Id::COMPONENT_UNDER_TEST, Id::COMPONENT_THAT_RECEIVES, LinkType::DEFAULT_LINK_TYPE,
                 &dataProcessor_, &messageRouter_)
    {
    }

  protected:
    virtual void SetUp() override { stage_.runComponent(); }

    MockDataProcessor dataProcessor_;

    MockMessageRouter messageRouter_;

    PipelineStageBase stage_;
};

TEST_F(PipelineStageBaseTest, StoppingComponent)
{
    EXPECT_EQ(stage_.isComponentRunning(), true);

    stage_.stopComponent();

    EXPECT_EQ(stage_.isComponentRunning(), false);
}

TEST_F(PipelineStageBaseTest, ProcessData)
{
    unique_ptr<PipelineDataBase> pData;

    messageRouter_.sendMessage(make_unique<PipelineDataMessage>(
        Id::COMPONENT_THAT_SENDS, Id::COMPONENT_UNDER_TEST, 0, pData));

    // wait for message to be forwarded
    while (messageRouter_.canReceive(Id::COMPONENT_THAT_RECEIVES) == false)
        ;

    auto pReceivedMessage = messageRouter_.receiveMessage(Id::COMPONENT_THAT_RECEIVES);

    EXPECT_EQ(pReceivedMessage->getSource(), Id::COMPONENT_UNDER_TEST);
}

}  // namespace pipeline