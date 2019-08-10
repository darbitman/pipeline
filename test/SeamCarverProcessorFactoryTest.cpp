#include "gtest/gtest.h"

#include <memory>

#include "SeamCarverProcessorFactory.hpp"

using std::dynamic_pointer_cast;
using std::make_shared;
using std::shared_ptr;

namespace sc
{
TEST(SeamCarverProcessorFactoryTest, CreateNullStage)
{
    auto pStage =
        SeamCarverProcessorFactory::getFactoryInstance().createStage((EPipelineStageId)(-1));

    EXPECT_EQ(pStage, nullptr);
}

TEST(SeamCarverProcessorFactoryTest, CreateValidStages)
{
    auto pStage =
        SeamCarverProcessorFactory::getFactoryInstance().createStage(EPipelineStageId::STAGE_0);

    EXPECT_NE(pStage, nullptr);

    pStage =
        SeamCarverProcessorFactory::getFactoryInstance().createStage(EPipelineStageId::STAGE_1);

    EXPECT_NE(pStage, nullptr);

    pStage =
        SeamCarverProcessorFactory::getFactoryInstance().createStage(EPipelineStageId::STAGE_2);

    EXPECT_NE(pStage, nullptr);

    pStage =
        SeamCarverProcessorFactory::getFactoryInstance().createStage(EPipelineStageId::STAGE_3);

    EXPECT_NE(pStage, nullptr);

    pStage =
        SeamCarverProcessorFactory::getFactoryInstance().createStage(EPipelineStageId::STAGE_4);

    EXPECT_NE(pStage, nullptr);
}

}  // namespace sc
