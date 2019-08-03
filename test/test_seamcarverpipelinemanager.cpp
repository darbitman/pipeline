#include "gtest/gtest.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "pipelineconfigurationtype.hpp"
#include "seamcarverpipelinemanager.hpp"

using namespace sc;

namespace seamcarver_test
{
namespace
{
class ServerCarverPipelineManagerTest : public ::testing::Test
{
protected:
    ServerCarverPipelineManagerTest() : mgr(PipelineConfigurationType::VERTICAL_DEFAULT) {}

    virtual void SetUp() override {}

    SeamCarverPipelineManager mgr;
};

TEST_F(ServerCarverPipelineManagerTest, InitializeRunStop)
{
    ASSERT_EQ(mgr.isInitialized(), false);
    ASSERT_EQ(mgr.arePipelineStagesCreated(), false);
    ASSERT_EQ(mgr.arePipelineStagesInitialized(), false);
    ASSERT_EQ(mgr.arePipelineStagesRunning(), false);
    mgr.initialize();
    ASSERT_EQ(mgr.isInitialized(), true);
    ASSERT_EQ(mgr.arePipelineStagesCreated(), true);
    ASSERT_EQ(mgr.arePipelineStagesInitialized(), true);
    ASSERT_EQ(mgr.arePipelineStagesRunning(), false);

    mgr.runPipelineStages();

    ASSERT_EQ(mgr.arePipelineStagesRunning(), true);

    auto interface = mgr.createPipelineInterface();

    ASSERT_EQ(interface->doesNewResultExist(), false);

    mgr.stopPipelineStages();

    while (mgr.arePipelineStagesRunning())
        ;

    EXPECT_EQ(mgr.arePipelineStagesRunning(), false);
}

TEST_F(ServerCarverPipelineManagerTest, AddRemoveStageDynamically)
{
    mgr.initialize();

    auto initialNumberOfPipelineStages = mgr.getNumberOfPipelineStages();

    EXPECT_EQ(mgr.removePipelineStage(PipelineStages::STAGE_1), false);

    EXPECT_EQ(mgr.addNewPipelineStage(PipelineStages::STAGE_1), true);

    ASSERT_EQ(mgr.getNumberOfPipelineStages(), initialNumberOfPipelineStages);

    mgr.runPipelineStages();

    mgr.removePipelineStage(PipelineStages::STAGE_1);
}


}  // namespace
}  // namespace seamcarver_test