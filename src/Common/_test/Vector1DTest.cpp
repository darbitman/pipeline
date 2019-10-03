#include "gtest/gtest.h"

#include <cstdint>
#include <iostream>

#include "Vector1D.hpp"

using std::cout;

namespace pipeline
{
class Vector1DTest : public ::testing::Test
{
  public:
    struct Data
    {
        Data(uint32_t a, uint32_t b, uint32_t c) noexcept : a_(a), b_(b), c_(c)
        {
            cout << "Calling constructor @ " << this << '\n';
            cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        ~Data()
        {
            cout << "Calling destructor @ " << this << '\n';
            cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        Data(const Data& other) noexcept
        {
            a_ = other.a_;
            b_ = other.b_;
            c_ = other.c_;
            cout << "Calling copy constructor @ " << this << '\n';
            cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        Data(Data&& other) noexcept
        {
            a_ = other.a_;
            b_ = other.b_;
            c_ = other.c_;
            cout << "Calling move constructor @ " << this << '\n';
            cout << "a_ = " << a_ << " b_ = " << b_ << " c_ = " << c_ << '\n';
        }

        uint32_t a_;
        uint32_t b_;
        uint32_t c_;
    };
};

TEST_F(Vector1DTest, DefaultConstructor)
{
    Vector1D<Data> vec;
    vec.emplace_back(1, 2, 3);
    vec.emplace_back(4, 5, 6);
    vec.emplace_back(7, 8, 9);

    EXPECT_EQ(vec.at(0).a_, 1);
    EXPECT_EQ(vec.at(0).b_, 2);
    EXPECT_EQ(vec.at(0).c_, 3);

    EXPECT_THROW(vec.at(3), std::out_of_range);

    Data newData{3, 2, 1};
    vec.push_back(newData);
}

TEST_F(Vector1DTest, PredefinedSizeConstructor)
{
    constexpr size_t startingCapacity = 10;
    Vector1D<Data> vec(startingCapacity);
    vec.emplace_back(1, 2, 3);
    vec.emplace_back(4, 5, 6);
    vec.emplace_back(7, 8, 9);

    EXPECT_EQ(vec.at(0).a_, 1);
    EXPECT_EQ(vec.at(0).b_, 2);
    EXPECT_EQ(vec.at(0).c_, 3);

    EXPECT_THROW(vec.at(3), std::out_of_range);

    EXPECT_GE(vec.capacity(), startingCapacity);
}

}  // namespace pipeline
