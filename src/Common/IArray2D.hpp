#pragma once

#include <cstdint>
#include <utility>

template <typename T>
class IArray2D
{
  public:
    virtual ~IArray2D() = default;

    /// @brief Resizes the array to new dimensions. This may not preserve the old data, however if
    /// the call fails (returns false), the old data will not be altered.
    /// @param numRows
    /// @param numColumns
    /// @return bool Returns true if the method succeeds, otherwise false.
    virtual bool resize(size_t numRows, size_t numColumns) noexcept = 0;

    /// @brief Returns the dimension of the 2D array
    /// @return std::pair<size_t, size_t> First is height (number of rows), second is width (number
    /// of columns)
    virtual std::pair<size_t, size_t> size() const noexcept = 0;

    /// @brief Returns a reference to the value in the array given by position (row, column)
    /// @param row
    /// @param column
    /// @throw std::out_of_range If the position exceeds the dimensions
    virtual T& at(size_t row, size_t column) = 0;

    /// @brief Returns a reference to the value in the array given by position (row, column)
    /// @param row
    /// @param column
    /// @throw std::out_of_range If the position exceeds the dimensions
    virtual const T& at(size_t row, size_t column) const = 0;

    /// @brief Returns a reference to the value in the array given by position (row, column)
    /// @param row
    /// @param column
    /// @throw std::out_of_range If the position exceeds the dimensions
    virtual T& operator()(size_t row, size_t column) = 0;

    /// @brief Returns a reference to the value in the array given by position (row, column)
    /// @param row
    /// @param column
    /// @throw std::out_of_range If the position exceeds the dimensions
    virtual const T& operator()(size_t row, size_t column) const = 0;
};
