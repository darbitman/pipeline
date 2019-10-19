#pragma once

#include <stdexcept>
#include <vector>

#include "IArray2D.hpp"

namespace pipeline
{
template <typename T>
class Vector2D : public IArray2D<T>
{
  public:
    Vector2D(size_t numRows, size_t numColumns)
        : maxRows_(numRows),
          maxColumns_(numColumns),

          maxElements_(numRows * numColumns),
          numRows_(numRows),
          numColumns_(numColumns),
          array_(maxElements_)
    {
    }

    virtual ~Vector2D() = default;

    virtual void resize(size_t numRows, size_t numColumns) noexcept override
    {
        // for fast resizing, don't change the array size if only need to use a subset of its
        // allocated memory
        if (numRows * numColumns <= maxElements_)
        {
            numRows_ = numRows;
            numColumns_ = numColumns;

            numElements_ = numRows * numColumns;
        }

        // need more elements than the array can support, it needs to be resized
        else
        {
            maxElements_ = numRows * numColumns;
            numElements_ = maxElements_;

            numRows_ = numRows;
            numColumns_ = numColumns;

            array_.resize(maxElements_);
        }
    }

    virtual std::pair<size_t, size_t> size() const noexcept override
    {
        return std::pair<size_t, size_t>(numRows_, numColumns_);
    }

    virtual T& at(size_t row, size_t column) override
    {
        return array_.at(FlattenDimensions(row, column));
    }

    virtual const T& at(size_t row, size_t column) const override
    {
        return array_.at(FlattenDimensions(row, column));
    }

    virtual T& operator()(size_t row, size_t column) override
    {
        return array_.at(FlattenDimensions(row, column));
    }

    virtual const T& operator()(size_t row, size_t column) const override
    {
        return array_.at(FlattenDimensions(row, column));
    }

  private:
    size_t FlattenDimensions(size_t row, size_t column) const noexcept
    {
        return (row * numColumns_) + column;
    }

    /// Maximum number of elements the array can store
    size_t maxElements_;

    /// Number of rows & columns used for storing data in the array
    /// These can be <= the maximum number of rows & columns
    size_t numRows_;
    size_t numColumns_;

    /// Number elements the array is storing
    size_t numElements_;

    std::vector<T> array_;
};

}  // namespace pipeline
