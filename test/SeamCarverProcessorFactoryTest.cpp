#include "gtest/gtest.h"

#include <memory>

#include "SeamCarverProcessorFactory.hpp"
#include "ComputeEnergy.hpp"

using std::make_shared;
using std::shared_ptr;
using std::dynamic_pointer_cast;

namespace sc
{
TEST(SeamCarverProcessorFactoryTest, CreateNullStage)
{
    ComputeEnergy a;
    // auto pStage =
    //     SeamCarverProcessorFactory::getFactoryInstance().createStage((EPipelineStageId)(-1));

    // EXPECT_EQ(pStage, nullptr);
}

// TEST(SeamCarverProcessorFactoryTest, CreateValidStage)
// {
//     auto pStage =
//        SeamCarverProcessorFactory::getFactoryInstance().createStage(EPipelineStageId::STAGE_0);

//     EXPECT_NE(pStage, nullptr);
// }

}  // namespace sc
