#pragma once

#include <stdexcept>

#include "ArrayAccessor1D.hpp"

namespace pipeline
{
template <typename T>
class Array2D
{
  public:
    Array2D(size_t width, size_t height)
        : maxWidth_(width),
          maxHeight_(height),
          totalSize_(maxWidth_ * maxHeight_),
          pArray_(reinterpret_cast<T*>(::operator new(sizeof(T) * totalSize_)))
    {
    }

    ~Array2D() { DestructAndFreeCurrentMemory(); }

    std::pair<size_t, size_t> size() const noexcept
    {
        return std::pair<size_t, size_t>(maxWidth_, maxHeight_);
    }

    ArrayAccessor1D<T> operator[](size_t yPos) const
    {
        VerifyHeight(yPos);
        T* pArray = CalculateRowPointer(yPos);
        return ArrayAccessor1D<T>(pArray, maxWidth_);
    }

    ArrayAccessor1D<T> operator[](size_t yPos)
    {
        VerifyHeight(yPos);
        T* pArray = CalculateRowPointer(yPos);
        return ArrayAccessor1D<T>(pArray, maxWidth_);
    }

    ArrayAccessor1D<T> at(size_t yPos) const
    {
        VerifyHeight(yPos);
        T* pArray = CalculateRowPointer(yPos);
        return ArrayAccessor1D<T>(pArray, maxWidth_);
    }

    ArrayAccessor1D<T> at(size_t yPos)
    {
        VerifyHeight(yPos);
        T* pArray = CalculateRowPointer(yPos);
        return ArrayAccessor1D<T>(pArray, maxWidth_);
    }

    T& at(size_t xPos, size_t yPos)
    {
        VerifyDimensionAccess(xPos, yPos);
        return pArray_[FlattenDimensions(xPos, yPos)];
    }

    const T& at(size_t xPos, size_t yPos) const
    {
        VerifyDimensionAccess(xPos, yPos);
        return pArray_[FlattenDimensions(xPos, yPos)];
    }

  private:
    size_t FlattenDimensions(size_t xPos, size_t yPos) { return (yPos * maxWidth_) + xPos; }

    void VerifyDimensionAccess(size_t xPos, size_t yPos)
    {
        VerifyWidth(xPos);
        VerifyHeight(yPos);
    }

    void VerifyWidth(size_t xPos)
    {
        if (xPos >= maxWidth_)
        {
            throw std::out_of_range("");
        }
    }

    void VerifyHeight(size_t yPos)
    {
        if (yPos >= maxHeight_)
        {
            throw std::out_of_range("");
        }
    }

    void DestructAndFreeCurrentMemory()
    {
        for (size_t i = 0; i < totalSize_; ++i)
        {
            // explicitly need to call destructor since placement new was used
            (pArray_ + i)->~T();
        }

        // free the memory
        ::operator delete(pArray_);
    }

    T* CalculateRowPointer(size_t yPos) { return pArray_ + (yPos * maxWidth_); }

    size_t maxWidth_;
    size_t maxHeight_;
    size_t totalSize_;

    T* pArray_{nullptr};
};

}  // namespace pipeline
