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

    /// @brief Returns the dimensions of 2D Array
    /// @return std::pair<size_t, size_t> First is width, second is height
    std::pair<size_t, size_t> size() const noexcept
    {
        return std::pair<size_t, size_t>(maxWidth_, maxHeight_);
    }

    /// @brief Returns an ArrayAccessor1D<T> which is an accessor for the particular row given by
    /// yPos
    /// @param yPos
    /// @return ArrayAccessor1D<T>
    /// @throw std::out_of_range For out of bounds yPos
    ArrayAccessor1D<T> operator[](size_t yPos) const { return at(yPos); }

    /// @brief Returns an ArrayAccessor1D<T> which is an accessor for the particular row given by
    /// yPos
    /// @param yPos
    /// @return ArrayAccessor1D<T>
    /// @throw std::out_of_range For out of bounds yPos
    ArrayAccessor1D<T> operator[](size_t yPos) { return at(yPos); }

    /// @brief Returns an ArrayAccessor1D<T> which is an accessor for the particular row given by
    /// yPos
    /// @param yPos
    /// @return ArrayAccessor1D<T>
    /// @throw std::out_of_range For out of bounds yPos
    ArrayAccessor1D<T> at(size_t yPos) const
    {
        VerifyHeight(yPos);
        T* pArray = CalculateRowPointer(yPos);
        return ArrayAccessor1D<T>(pArray, maxWidth_);
    }

    /// @brief Returns an ArrayAccessor1D<T> which is an accessor for the particular row given by
    /// yPos
    /// @param yPos
    /// @return ArrayAccessor1D<T>
    /// @throw std::out_of_range For out of bounds yPos
    ArrayAccessor1D<T> at(size_t yPos)
    {
        VerifyHeight(yPos);
        T* pArray = CalculateRowPointer(yPos);
        return ArrayAccessor1D<T>(pArray, maxWidth_);
    }

    /// @brief Returns a reference to an object specified by the index
    /// @param xPos
    /// @param yPos
    /// @return T&
    /// @throw std::out_of_range If the dimensions are out of bounds
    T& at(size_t xPos, size_t yPos)
    {
        VerifyDimensionAccess(xPos, yPos);
        return pArray_[FlattenDimensions(xPos, yPos)];
    }

    /// @brief Returns a reference to an object specified by the index
    /// @param xPos
    /// @param yPos
    /// @return const T&
    /// @throw std::out_of_range If the dimensions are out of bounds
    const T& at(size_t xPos, size_t yPos) const
    {
        VerifyDimensionAccess(xPos, yPos);
        return pArray_[FlattenDimensions(xPos, yPos)];
    }

    Array2D(const Array2D&) = delete;
    Array2D(Array2D&&) = delete;
    Array2D& operator=(const Array2D&) = delete;
    Array2D& operator=(Array2D&&) = delete;

  private:
    /// @brief Convert 2D dimensions to linear dimension
    /// @param xPos
    /// @param yPos
    /// @return size_t Linear dimension
    size_t FlattenDimensions(size_t xPos, size_t yPos) { return (yPos * maxWidth_) + xPos; }

    /// @brief Check for out of bound dimensions
    /// @param xPos
    /// @param yPos
    /// @throw std::out_of_range If the dimensions are out of bounds
    void VerifyDimensionAccess(size_t xPos, size_t yPos)
    {
        VerifyWidth(xPos);
        VerifyHeight(yPos);
    }

    /// @brief Check for out of bound dimensions
    /// @param xPos
    /// @throw std::out_of_range If the dimensions are out of bounds
    void VerifyWidth(size_t xPos)
    {
        if (xPos >= maxWidth_)
        {
            throw std::out_of_range("");
        }
    }

    /// @brief Check for out of bound dimensions
    /// @param yPos
    /// @throw std::out_of_range If the dimensions are out of bounds
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
