#include "gtest/gtest.h"

#include <chrono>
#include <cstdint>
#include <memory>
#include <thread>
#include <vector>

#include "cumulativepathenergycalculatorstage.hpp"
#include "pipelinestages.hpp"
#include "sharedqueue.hpp"
#include "VerticalSeamCarverData.hpp"

using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::chrono::seconds;
using std::this_thread::sleep_for;
using namespace sc;

namespace seamcarver_test
{
namespace
{
class CumulativePathEnergyCalculatorStageTest : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        pQueueManager_ = make_shared<SeamCarverQueueManager>();

        vector<int32_t> queue_ids;
        vector<PipelineQueueTypes> queue_types;

        queue_ids.push_back(PipelineStages::STAGE_1);
        queue_types.push_back(PipelineQueueTypes::QUEUETYPE_FIFO);

        queue_ids.push_back(PipelineStages::STAGE_2);
        queue_types.push_back(PipelineQueueTypes::QUEUETYPE_FIFO);

        pQueueManager_->initialize(queue_ids, queue_types);

        pSenderRcvr_ = make_shared<SeamCarverSendRcvMgr>(pQueueManager_);

        pStage = make_shared<CumulativePathEnergyCalculatorStage>();

        pStage->initialize(pSenderRcvr_);
    }

    shared_ptr<SeamCarverQueueManager> pQueueManager_;

    shared_ptr<SeamCarverSendRcvMgr> pSenderRcvr_;

    shared_ptr<SeamCarverStage> pStage;
};

TEST_F(CumulativePathEnergyCalculatorStageTest, Initialize)
{
    ASSERT_EQ(pStage->isInitialized(), true);
}

TEST_F(CumulativePathEnergyCalculatorStageTest, RunStopStage)
{
    ASSERT_EQ(pStage->isRunning(), false);

    pStage->runStage();

    while (!pStage->isRunning())
        ;

    ASSERT_EQ(pStage->isRunning(), true);

    pStage->stopStage();

    while (pStage->isRunning())
        ;

    ASSERT_EQ(pStage->isRunning(), false);
}

TEST_F(CumulativePathEnergyCalculatorStageTest, TestQueues)
{
    pStage->runStage();

    while (!pStage->isRunning())
        ;

    VerticalSeamCarverData* pDataToSend = new VerticalSeamCarverData();

    // send FROM STAGE_0
    pSenderRcvr_->Send(pDataToSend, PipelineStages::STAGE_0);

    // wait for data to arrive at STAGE_0
    while (!pSenderRcvr_->canReceive(PipelineStages::STAGE_2))
        ;

    EXPECT_EQ(pSenderRcvr_->canReceive(PipelineStages::STAGE_2), true);

    auto pDataReceived = pSenderRcvr_->Receive(PipelineStages::STAGE_2);

    EXPECT_NE(pDataReceived, nullptr);

    EXPECT_EQ(pDataToSend, pDataReceived);

    pStage->stopStage();

    while (pStage->isRunning())
        ;

    ASSERT_EQ(pStage->isRunning(), false);
}
}  // namespace
}  // namespace seamcarver_test
