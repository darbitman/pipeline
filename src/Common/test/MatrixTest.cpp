#include "gtest/gtest.h"

#include <cstdint>
#include <iostream>

#include "Matrix.hpp"

using std::cout;

namespace pipeline_test
{
class MatrixTest : public ::testing::Test
{
  public:
    MatrixTest() : matrix(initRows, initColumns) {}

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

  protected:
    virtual void SetUp() override {}

    static constexpr size_t initRows = 6;
    static constexpr size_t initColumns = 8;

    pipeline::Matrix<Data> matrix;
};

TEST_F(MatrixTest, VerifySize)
{
    std::pair<size_t, size_t> dimensions = matrix.size();

    EXPECT_EQ(dimensions.first, initRows);
    EXPECT_EQ(dimensions.second, initColumns);
}

TEST_F(MatrixTest, AccessValidDimensions)
{
    constexpr uint32_t A = 10;
    constexpr uint32_t B = 20;
    constexpr uint32_t C = 30;

    // Set data
    EXPECT_NO_THROW(matrix(0, 0).a_ = A);
    EXPECT_NO_THROW(matrix(0, 0).b_ = B);
    EXPECT_NO_THROW(matrix(0, 0).c_ = C);

    // Verify data was set
    EXPECT_EQ(matrix(0, 0).a_, A);
    EXPECT_EQ(matrix(0, 0).b_, B);
    EXPECT_EQ(matrix(0, 0).c_, C);
}

TEST_F(MatrixTest, AccessInvalidDimensions)
{
    // Access when both indices are out of bounds
    EXPECT_THROW(matrix(initRows, initColumns), std::out_of_range);

    // Accesss when row index is out of bounds
    EXPECT_THROW(matrix(initRows, initColumns - 1), std::out_of_range);

    // Access when column index is out of bounds
    EXPECT_THROW(matrix(initRows - 1, initColumns), std::out_of_range);
}

TEST_F(MatrixTest, ResizeAndAccess)
{
    constexpr uint32_t A = 10;
    constexpr uint32_t B = 20;
    constexpr uint32_t C = 30;

    constexpr size_t newRows = 2 * initRows;
    constexpr size_t newColumns = 2 * initColumns;

    // Resize the matrix
    matrix.resize(newRows, newColumns);

    // Read back its dimensions
    std::pair<size_t, size_t> dimensions = matrix.size();

    EXPECT_EQ(dimensions.first, newRows);
    EXPECT_EQ(dimensions.second, newColumns);

    // attempt to set data using new dimensions
    EXPECT_NO_THROW(matrix(newRows - 1, newColumns - 1).a_ = A);
    EXPECT_NO_THROW(matrix(newRows - 1, newColumns - 1).b_ = B);
    EXPECT_NO_THROW(matrix(newRows - 1, newColumns - 1).c_ = C);

    // Access the data
    EXPECT_EQ(matrix(newRows - 1, newColumns - 1).a_, A);
    EXPECT_EQ(matrix(newRows - 1, newColumns - 1).b_, B);
    EXPECT_EQ(matrix(newRows - 1, newColumns - 1).c_, C);

    // Access out of bounds
    EXPECT_THROW(matrix(newRows, newColumns), std::out_of_range);
}

TEST_F(MatrixTest, InitializeObjectInPlace)
{
    constexpr uint32_t A = 10;
    constexpr uint32_t B = 20;
    constexpr uint32_t C = 30;

    matrix.emplace(0, 0, A, B, C);

    // Verify object was built in place
    EXPECT_EQ(matrix(0, 0).a_, A);
    EXPECT_EQ(matrix(0, 0).b_, B);
    EXPECT_EQ(matrix(0, 0).c_, C);
}

}  // namespace pipeline_test
