#include "gtest/gtest.h"

#include <cstdint>
#include <iostream>

#include "Array2D.hpp"

using std::cout;

namespace pipeline
{
class Array2DTest : public ::testing::Test
{
  public:
    struct Data
    {
        Data(uint32_t a, uint32_t b, uint32_t c) noexcept : a_(a), b_(b), c_(c)
        {
            // cout << "Calling constructor @ " << this << '\n';
            // cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        ~Data()
        {
            // cout << "Calling destructor @ " << this << '\n';
            // cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
            a_ = 0;
            b_ = 0;
            c_ = 0;
        }

        Data(const Data& other) noexcept
        {
            a_ = other.a_;
            b_ = other.b_;
            c_ = other.c_;
            // cout << "Calling copy constructor @ " << this << '\n';
            // cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        Data(Data&& other) noexcept
        {
            a_ = other.a_;
            b_ = other.b_;
            c_ = other.c_;
            // cout << "Calling move constructor @ " << this << '\n';
            // cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        uint32_t a_;
        uint32_t b_;
        uint32_t c_;
    };
};

TEST_F(Array2DTest, CheckSizes)
{
    constexpr size_t width{10};
    constexpr size_t height{25};
    Array2D<Data> vec(width, height);

    EXPECT_EQ(vec.size().first, width);
    EXPECT_EQ(vec.size().second, height);
}

TEST_F(Array2DTest, AccessArray)
{
    constexpr size_t width{10};
    constexpr size_t height{25};
    Array2D<Data> vec(width, height);

    vec.at(3).at(3).a_ = 12;

    ASSERT_EQ(vec.at(3).at(3).a_, 12);
}

}  // namespace pipeline
