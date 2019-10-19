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

    Matrix(Matrix&& other) noexcept
        : maxRows_(other.maxRows_),
          maxElements_(other.maxElements_),
          numRows_(other.numRows_),
          numColumns_(other.numColumns_),
          p2DArray_(other.p2DArray_)
    {
        other.maxRows_ = 0;
        other.maxElements_ = 0;
        other.numRows_ = 0;
        other.numColumns_ = 0;
        other.p2DArray_ = nullptr;
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
            // Index 0 of p2DArray_ still points to the same contiguous array
            UpdateArrayOfRowPointers(p2DArray_, numRows, numColumns);

            // set new dimensions
            numRows_ = numRows;
            numColumns_ = numColumns;
            numElements_ = numRows * numColumns;

            // Don't update the max variables because arrays have not changed
        }

        // If more rows are needed, but total number of elements doesn't increase, then only the
        // array of pointers has to change, while keeping the contiguous array (which holds the
        // actual objects) intact
        else if (numRows > maxRows_ && (numRows * numColumns) <= maxElements_)
        {
            // preserve pointer to contiguous array
            T* pContiguousArray = p2DArray_[0];

            // free the memory allocated for storing pointers to the contiguous array
            ::operator delete(p2DArray_);

            // allocate new array that will hold pointers to each 'row' in the contiguous
            // array
            p2DArray_ = reinterpret_cast<T**>((::operator new(numRows * sizeof(T*))));

            // Set index 0 of the array of pointers to point to the beginning of the contiguous
            // array
            p2DArray_[0] = pContiguousArray;

            UpdateArrayOfRowPointers(p2DArray_, numRows, numColumns);

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
            InvokeAllObjectDestructors();

            // free the memory allocated for contiguous array
            ::operator delete(p2DArray_[0]);

            // since maxElements has been exceed, the value can be updated
            // allocate new contiguous memory for storing objects
            maxElements_ = numElements_ = numRows * numColumns;
            p2DArray_[0] = reinterpret_cast<T*>(::operator new(maxElements_ * sizeof(T)));

            UpdateArrayOfRowPointers(p2DArray_, numRows, numColumns);

            // update dimensions
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
    Matrix& operator=(const Matrix&) = delete;
    Matrix& operator=(Matrix&&) = delete;

  private:
    bool VerifyDimensionAccess(const size_t row, const size_t column) const noexcept
    {
        return (VerifyRowAccess(row) && VerifyColumnAccess(column));
    }

    bool VerifyRowAccess(const size_t row) const noexcept { return row < numRows_; }

    bool VerifyColumnAccess(const size_t column) const noexcept { return column < numColumns_; }

    void DestructAndFreeCurrentMemory() noexcept
    {
        InvokeAllObjectDestructors();

        DeallocateMemory();
    }

    T** AllocateMatrix(size_t numRows, size_t numColumns)
    {
        size_t numElements = numRows * numColumns;

        // create an array of pointers that will hold pointers to each 'row' in the contiguous array
        T** pArrayOfPointers = reinterpret_cast<T**>((::operator new(numRows * sizeof(T*))));

        // first entry in the array of pointers points to the beginning of the linear array
        // create contiguous array
        pArrayOfPointers[0] = reinterpret_cast<T*>(::operator new(numElements * sizeof(T)));

        UpdateArrayOfRowPointers(pArrayOfPointers, numRows, numColumns);

        return pArrayOfPointers;
    }

    /// @param pArrayOfPointers Points to the array of pointers that point to each 'row' in the
    /// contiguous array. Index 0 of this array must be initialized to point to the beginning of the
    /// contiguous array prior to calling this method.
    /// @param numRows The number of rows
    /// @param numColumns The number of columns in each row
    void UpdateArrayOfRowPointers(T** pArrayOfPointers, size_t numRows, size_t numColumns)
    {
        if (pArrayOfPointers != nullptr)
        {
            // Update each pointer in the array to point to the next 'row' in the contigous array
            for (size_t row = 1; row < numRows; ++row)
            {
                // current pointer points to where the previous pointer points to plus an offset
                // determined by the number of columns (ie points to the next 'row' in the
                // contiguous array);
                pArrayOfPointers[row] = pArrayOfPointers[row - 1] + numColumns;
            }
        }
    }

    /// @brief Invokes the destructors of all the elements in the contiguous array
    void InvokeAllObjectDestructors() noexcept
    {
        if (p2DArray_ != nullptr)
        {
            // explicitly need to call destructor since placement new was used for elements in the
            // contiguous array
            for (size_t i = 0; i < maxElements_; ++i)
            {
                p2DArray_[0][i].~T();
            }
        }
    }

    void DeallocateMemory() noexcept
    {
        if (p2DArray_ != nullptr)
        {
            // free the memory allocated for contigious memory (this is where the objects are
            // stored)
            ::operator delete(p2DArray_[0]);

            // free the memory allocated for storing pointers to the contigous memory
            ::operator delete(p2DArray_);

            p2DArray_ = nullptr;
        }
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
