#pragma once

#include <stdexcept>

#include "IArray2D.hpp"

namespace pipeline
{
template <typename T>
class Matrix : public IArray2D<T>
{
  public:
    Matrix(size_t numRows, size_t numColumns)
        : maxRows_(numRows),
          maxColumns_(numColumns),
          maxElements_(numRows * numColumns),
          numRows_(numRows),
          numColumns_(numColumns),
          numElements_(numRows * numColumns),
          pArray_(AllocateMatrix(numRows, numColumns))
    {
    }

    virtual ~Matrix() { DestructAndFreeCurrentMemory(); }

    virtual bool resize(size_t numRows, size_t numColumns) noexcept override
    {
        // if numRows/numColumns are both less than the current maxRows/maxColumns, just change the
        // dimensions of the data
        if (numRows <= maxRows_ && numColumns <= maxColumns_)
        {
            numRows_ = numRows;
            numColumns_ = numColumns;
            numElements_ = numRows * numColumns;

            return true;
        }

        // otherwise need to free the current memory and reallocate
        else
        {
            DestructAndFreeCurrentMemory();
            pArray_ = AllocateMatrix(numRows, numColumns);

            maxRows_ = numRows;
            maxColumns_ = numColumns;
            maxElements_ = numRows * numColumns;

            numRows_ = numRows;
            numColumns_ = numColumns;
            numElements_ = maxElements_;

            return true;
        }
    }

    virtual std::pair<size_t, size_t> size() const noexcept override
    {
        return std::pair<size_t, size_t>(numRows_, numColumns_);
    }

    virtual T& at(size_t row, size_t column) override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return pArray_[row][column];
    }

    virtual const T& at(size_t row, size_t column) const override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return pArray_[row][column];
    }

    virtual T& operator()(size_t row, size_t column) override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return pArray_[row][column];
    }

    virtual const T& operator()(size_t row, size_t column) const override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return pArray_[row][column];
    }

    Matrix(const Matrix&) = delete;
    Matrix(Matrix&&) = delete;
    Matrix& operator=(const Matrix&) = delete;
    Matrix& operator=(Matrix&&) = delete;

  private:
    bool VerifyDimensionAccess(const size_t row, const size_t column) const noexcept
    {
        // TODO
        return true;
    }

    bool VerifyWidth(const size_t column) const noexcept
    {
        // TODO
        return true;
    }

    bool VerifyHeight(const size_t row) const noexcept
    {
        // TODO
        return true;
    }

    void DestructAndFreeCurrentMemory()
    {
        // explicitly need to call destructor since placement new was used for elements in the
        // linear array
        for (size_t i = 0; i < maxElements_; ++i)
        {
            pArray_[0][i].~T();
        }

        // free the memory allocated for contigious memory (this is where the objects are stored)
        ::operator delete(pArray_[0]);

        // free the memory allocated for storing pointers to the contigous memory
        ::operator delete(pArray_);

        pArray_ = nullptr;
    }

    T** AllocateMatrix(size_t numRows, size_t numColumns)
    {
        size_t numElements = numRows * numColumns;

        // create an array of pointers that will hold pointers to each 'row' in the contiguous array
        T** pArrayOfPointers = reinterpret_cast<T**>((::operator new(numRows * sizeof(T*))));

        // first entry in the array of pointers points to the beginning of the linear array
        // create contiguous array
        pArrayOfPointers[0] = reinterpret_cast<T*>(::operator new(numElements * sizeof(T)));

        // Update each pointer in the array to point to the next 'row' in the contigous array
        for (size_t row = 1; row < numRows; ++row)
        {
            // current pointer points to where the previous pointer points to plus an offset of the
            // number of columns (ie points to the next row)
            pArrayOfPointers[row] = pArrayOfPointers[row - 1] + numColumns;
        }

        return pArrayOfPointers;
    }

    /// Maximum number of rows & columns in array
    size_t maxRows_;
    size_t maxColumns_;

    /// Maximum number of elements the array can store
    size_t maxElements_;

    /// Number of rows & columns used for storing data in the array
    /// These can be <= the maximum number of rows & columns
    size_t numRows_;
    size_t numColumns_;

    /// Total number of elements in the array
    size_t numElements_;

    /// Array of pointers to 'rows' in the linear array
    /// This dual dereferencing allows for using double array subscripts (ie [x][y])
    T** pArray_{nullptr};
};

}  // namespace pipeline
