#include "gtest/gtest.h"

#include <cstdint>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

#include "pipelinequeuetypes.hpp"
#include "pipelinestages.hpp"
#include "seamcarverpipelineinterface.hpp"
#include "seamcarverqueuemanager.hpp"
#include "seamcarversendrcvmgr.hpp"
#include "sharedqueue.hpp"
#include "VerticalSeamCarverData.hpp"

using std::make_shared;
using std::shared_ptr;
using std::vector;
using namespace sc;

namespace seamcarver_test
{
class SeamCarverSendRcvMgrHolder
{
public:
    SeamCarverSendRcvMgrHolder()
    {
        pQueueManager_ = make_shared<SeamCarverQueueManager>();

        vector<int32_t> queue_ids;
        vector<PipelineQueueTypes> queue_types;

        queue_ids.push_back(PipelineStages::STAGE_0);
        queue_types.push_back(PipelineQueueTypes::QUEUETYPE_FIFO);

        queue_ids.push_back(PipelineStages::LAST_QUEUE_STAGE);
        queue_types.push_back(PipelineQueueTypes::QUEUETYPE_FIFO);

        pQueueManager_->initialize(queue_ids, queue_types);
    }

    virtual ~SeamCarverSendRcvMgrHolder() {}

    shared_ptr<SeamCarverSendRcvMgr> instance()
    {
        static shared_ptr<SeamCarverSendRcvMgr> pSenderReceiver =
            make_shared<SeamCarverSendRcvMgr>(pQueueManager_);
        return pSenderReceiver;
    }

private:
    shared_ptr<SeamCarverQueueManager> pQueueManager_;
};

class SeamCarverPipelineInterfaceTest : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        static SeamCarverSendRcvMgrHolder senderReceiverHolder;

        pSenderRcvr = senderReceiverHolder.instance();
    }

    SeamCarverPipelineInterface& getInstance()
    {
        // create an interface that uses the senderReceiver
        static SeamCarverPipelineInterface interface(pSenderRcvr);

        return interface;
    }

    shared_ptr<SeamCarverSendRcvMgr> pSenderRcvr;
};

TEST_F(SeamCarverPipelineInterfaceTest, NoFramesInEmptyPipeline)
{
    ASSERT_EQ(this->getInstance().getNumberOfFramesInPipeline(), 0);
    ASSERT_EQ(this->getInstance().doesNewResultExist(), false);
}

TEST_F(SeamCarverPipelineInterfaceTest, AddingFramesToInput)
{
    // create data to send
    shared_ptr<cv::Mat> pFrame = make_shared<cv::Mat>(cv::imread(IMG_PATH));

    // get a pointer to the SeamCarverSendRcvMgr
    SeamCarverSendRcvMgrHolder senderReceiverHolder;
    auto pSenderRcvr = senderReceiverHolder.instance();

    // the interface adds the frame to the input queue
    this->getInstance().addNewFrame(pFrame, 1);

    // the interface added the frame to the intput queue
    ASSERT_EQ(pSenderRcvr->canReceive(PipelineStages::STAGE_0), true);

    EXPECT_EQ(this->getInstance().getNumberOfFramesInPipeline(), 1);

    // the interface adds the frame to the input queue
    this->getInstance().addNewFrame(pFrame, 1);

    EXPECT_EQ(this->getInstance().getNumberOfFramesInPipeline(), 2);

    // the interface added the frame to the intput queue
    ASSERT_EQ(pSenderRcvr->canReceive(PipelineStages::STAGE_0), true);
}

TEST_F(SeamCarverPipelineInterfaceTest, RemovingFramesFromOutput)
{
    // create data to send
    shared_ptr<cv::Mat> pFrame = make_shared<cv::Mat>(cv::imread(IMG_PATH));

    // get a pointer to the SeamCarverSendRcvMgr
    SeamCarverSendRcvMgrHolder senderReceiverHolder;
    auto pSenderRcvr = senderReceiverHolder.instance();

    // create frame
    VerticalSeamCarverData* pData = new VerticalSeamCarverData();
    pData->saveImage(pFrame);

    // the SenderRcvr adds the frame to the output queue
    pSenderRcvr->Send(pData, PipelineStages::STAGE_4);

    ASSERT_EQ(this->getInstance().doesNewResultExist(), true);

    auto pReceivedFrame = this->getInstance().getNextFrame();

    EXPECT_NE(pReceivedFrame, nullptr);

    EXPECT_EQ(pReceivedFrame->rows, pFrame->rows);
    EXPECT_EQ(pReceivedFrame->cols, pFrame->cols);
}

}  // namespace seamcarver_test
