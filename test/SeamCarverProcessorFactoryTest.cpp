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
        SeamCarverProcessorFactory::createStage((EComponentId)(-1));

    EXPECT_EQ(pStage, nullptr);
}

TEST(SeamCarverProcessorFactoryTest, CreateValidStages)
{
    auto pRegisteredStages =
        SeamCarverProcessorFactory::getVectorOfRegisteredStages();

    for (size_t i = 0; i < pRegisteredStages->size(); ++i)
    {
        EXPECT_EQ(SeamCarverProcessorFactory::isComponentRegistered(
                      (*pRegisteredStages)[i]),
                  true);

        EXPECT_NE(
            SeamCarverProcessorFactory::createStage((*pRegisteredStages)[i]),
            nullptr);
    }
}

}  // namespace sc
