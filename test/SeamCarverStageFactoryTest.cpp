#include "gtest/gtest.h"

#include <memory>

#include "SeamCarverStageFactory.hpp"

using std::make_shared;
using std::shared_ptr;

namespace sc
{
TEST(SeamCarverStageFactoryTest, CreateNullStage)
{
    auto pStage =
        SeamCarverStageFactory::getFactoryInstance().createStage((EPipelineStageId)(-1), nullptr);

    EXPECT_EQ(pStage, nullptr);
}

TEST(SeamCarverStageFactoryTest, CreateValidStages)
{
    auto pStage = SeamCarverStageFactory::getFactoryInstance().createStage(
        EPipelineStageId::STAGE_0, nullptr);

    EXPECT_NE(pStage, nullptr);
}

}  // namespace sc
