#include "gtest/gtest.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "ThreadRunner.hpp"

namespace sc
{
class ThreadRunnerTest : public ::testing::Test
{
  public:
    virtual void Print()
    {
        std::cout << "Hello World" << '\n';
        while (1)
            ;
    }

  protected:
    virtual void SetUp() override
    {
        if (thread_ == nullptr)
        {
            thread_ = new ThreadRunner(&ThreadRunnerTest::Print, this);
        }
    }

    inline static ThreadRunner* thread_ = nullptr;
};

TEST_F(ThreadRunnerTest, DefaultThreadRunnerCtor)
{
    EXPECT_EQ(this->thread_->Detach(), true);
    EXPECT_EQ(this->thread_->Detach(), false);

    std::this_thread::sleep_for(std::chrono::seconds(3));
}

}  // namespace sc
