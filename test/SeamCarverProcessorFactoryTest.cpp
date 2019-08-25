#include "gtest/gtest.h"

#include <memory>

#include "PipelineCommon.hpp"
#include "SeamCarverProcessorFactory.hpp"

using std::dynamic_pointer_cast;
using std::make_unique;
using std::unique_ptr;

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
    auto pRegisteredStages =
        SeamCarverProcessorFactory::getFactoryInstance().getVectorOfRegisteredStages();

    for (size_t i = 0; i < pRegisteredStages->size(); ++i)
    {
        EXPECT_EQ(SeamCarverProcessorFactory::getFactoryInstance().isStageRegistered(
                      (*pRegisteredStages)[i]),
                  true);

        EXPECT_NE(
            SeamCarverProcessorFactory::getFactoryInstance().createStage((*pRegisteredStages)[i]),
            nullptr);
    }
}

}  // namespace sc
