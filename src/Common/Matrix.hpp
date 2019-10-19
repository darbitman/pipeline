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
          maxElements_(numRows * numColumns),
          numRows_(numRows),
          numColumns_(numColumns),
          numElements_(numRows * numColumns),
          p2DArray_(AllocateMatrix(numRows, numColumns))
    {
    }

    virtual ~Matrix() { DestructAndFreeCurrentMemory(); }

    virtual void resize(size_t numRows, size_t numColumns) noexcept override
    {
        // Resizing can be fast (ie not require memory deallocation) if numRows is less than
        // maxRows_ because the array of pointers is limited to maxRows_ and as long as the total
        // number of elements is less than maxElements_ because the contiguous array which holds the
        // actual objects is limited to maxElements_
        if (numRows <= maxRows_ && (numRows * numColumns) <= maxElements_)
        {
            // update array of pointers to point to new 'rows' in the contiguous array, where each
            // row has numColumns elements
            for (size_t row = 1; row < numRows; ++row)
            {
                p2DArray_[row] = p2DArray_[row - 1] + numColumns_;
            }

            // set new dimensions
            numRows_ = numRows;
            numColumns_ = numColumns;
            numElements_ = numRows * numColumns;
        }

        // If more rows are needed, but total number of elements doesn't increase, then only the
        // array of pointers has to change, while keeping the contiguous array (which holds the
        // actual objects) intact
        else if (numRows > maxRows_ && (numRows * numColumns) <= maxElements_)
        {
            // preserve pointer to contiguous array
            T* pContiguousArray = p2DArray_[0];

            // free the memory allocated for storing pointers to the contigous memory
            ::operator delete(p2DArray_);

            // allocate new memory that will hold pointers to each 'row' in the contiguous
            // array
            p2DArray_ = reinterpret_cast<T**>((::operator new(numRows * sizeof(T*))));

            // Set the pointer to the contiguous array
            p2DArray_[0] = pContiguousArray;

            // update array of pointers to point to new 'rows' in the contiguous array, where each
            // row has numColumns elements
            for (size_t row = 1; row < numRows; ++row)
            {
                p2DArray_[row] = p2DArray_[row - 1] + numColumns_;
            }

            // update dimensions
            maxRows_ = numRows;
            numRows_ = numRows;
            numColumns_ = numColumns;
            numElements_ = numRows * numColumns;
        }

        // If the number of rows stays the same, but the number of columns changes such that the
        // total number of elements that can be stored in the contiguous array is larger than
        // maxElements_, then the array of pointers can be preserved, while the contiguous array
        // will need to be deleted and reallocated
        else if (numRows <= maxRows_ && (numRows * numColumns) > maxElements_)
        {
            // Delete the objects explicitly by calling the destructor since placement new was used
            // for elements in the contiguous array
            for (size_t i = 0; i < maxElements_; ++i)
            {
                p2DArray_[0][i].~T();
            }

            // free the memory allocated for contiguous array
            ::operator delete(p2DArray_[0]);

            // allocate new contiguous memory for storing objects
            numElements_ = numRows * numColumns;
            p2DArray_[0] = reinterpret_cast<T*>(::operator new(numElements_ * sizeof(T)));

            // update array of pointers to point to new 'rows' in the contiguous array, where each
            // row has numColumns elements
            for (size_t row = 1; row < numRows; ++row)
            {
                p2DArray_[row] = p2DArray_[row - 1] + numColumns_;
            }

            // update dimensions
            maxElements_ = numElements_;
            numRows_ = numRows;
            numColumns_ = numColumns;
        }

        // otherwise need to free the current memory and reallocate if more rows and more elements
        else
        {
            DestructAndFreeCurrentMemory();
            p2DArray_ = AllocateMatrix(numRows, numColumns);

            maxRows_ = numRows;
            maxElements_ = numRows * numColumns;

            numRows_ = numRows;
            numColumns_ = numColumns;
            numElements_ = maxElements_;
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

        return p2DArray_[row][column];
    }

    virtual const T& at(size_t row, size_t column) const override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return p2DArray_[row][column];
    }

    virtual T& operator()(size_t row, size_t column) override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return p2DArray_[row][column];
    }

    virtual const T& operator()(size_t row, size_t column) const override
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        return p2DArray_[row][column];
    }

    template <typename... _ArgTypes>
    void emplace(size_t row, size_t column, _ArgTypes&&... __args)
    {
        if (!VerifyDimensionAccess(row, column))
        {
            throw std::out_of_range("");
        }

        // get pointer to the location at which to emplace
        T* pObject = &(p2DArray_[row][column]);

        // an object may exist at the location, so make sure to call its destructor
        pObject->~T();

        // call placement new to construct the object at that location
        new (pObject) T(std::forward<_ArgTypes>(__args)...);
    }

    Matrix(const Matrix&) = delete;
    Matrix(Matrix&&) = delete;
    Matrix& operator=(const Matrix&) = delete;
    Matrix& operator=(Matrix&&) = delete;

  private:
    bool VerifyDimensionAccess(const size_t row, const size_t column) const noexcept
    {
        return (VerifyRowAccess(row) && VerifyColumnAccess(column));
    }

    bool VerifyRowAccess(const size_t row) const noexcept { return row < numRows_; }

    bool VerifyColumnAccess(const size_t column) const noexcept { return column < numColumns_; }

    void DestructAndFreeCurrentMemory()
    {
        // explicitly need to call destructor since placement new was used for elements in the
        // linear array
        for (size_t i = 0; i < maxElements_; ++i)
        {
            p2DArray_[0][i].~T();
        }

        // free the memory allocated for contigious memory (this is where the objects are stored)
        ::operator delete(p2DArray_[0]);

        // free the memory allocated for storing pointers to the contigous memory
        ::operator delete(p2DArray_);

        p2DArray_ = nullptr;
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

    /// Maximum number of rows in array
    size_t maxRows_;

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
    T** p2DArray_{nullptr};
};

}  // namespace pipeline
