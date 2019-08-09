#include "gtest/gtest.h"

#include <cstdint>
#include <memory>
#include <thread>

#define private public
#define protected public
#include "ComputeEnergyStage.hpp"
#undef private
#undef protected
#define private private
#define protected protected

using std::make_shared;
using std::shared_ptr;

namespace sc
{
class ComputeEnergyStageTest : public ::testing::Test
{
  protected:
    virtual void SetUp() override
    {
        if (pSenderReceiver_ == nullptr)
        {
            pSenderReceiver_ = make_shared<PipelineSenderReceiver>();
        }

        if (pStage_ == nullptr)
        {
            pStage_ = make_shared<ComputeEnergyStage>(pSenderReceiver_);
        }
    }

    static shared_ptr<PipelineSenderReceiver> pSenderReceiver_;

    static shared_ptr<IPipelineStage> pStage_;
};

shared_ptr<PipelineSenderReceiver> ComputeEnergyStageTest::pSenderReceiver_;

shared_ptr<IPipelineStage> ComputeEnergyStageTest::pStage_;

TEST_F(ComputeEnergyStageTest, ProcessData)
{
    //
}

}  // namespace sc
