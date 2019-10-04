#pragma once

#include <stdexcept>

#include "Vector1D.hpp"

namespace pipeline
{
template <typename T>
class Vector2D
{
  public:
    Vector2D() = default;

    ~Vector2D() = default;

    std::pair<size_t, size_t> size() const noexcept
    {
        return std::pair<size_t, size_t>(max_width_, max_height_);
    }

    void reserve(size_t width, size_t height)
    {
        //
    }

    Vector1D<T> at(size_t y_pos)
    {
        return Vector1D<T>();
    }

    const Vector1D<T> at(size_t y_pos) const
    {
        return Vector1D<T>();
    }

    T& at(size_t x_pos, size_t y_pos)
    {
        VerifyDimensionAccess(x_pos, y_pos);
        //
    }

    const T& at(size_t x_pos, size_t y_pos) const
    {
        VerifyDimensionAccess(x_pos, y_pos);
        //
    }

  private:
    void VerifyDimensionAccess(size_t x_pos, size_t y_pos)
    {
        VerifyWidth(x_pos);
        VerifyHeight(y_pos);
    }

    void VerifyWidth(size_t x_pos)
    {
        if (x_pos >= max_width_)
        {
            throw std::out_of_range("");
        }
    }

    void VerifyHeight(size_t y_pos)
    {
        if (y_pos >= max_height_)
        {
            throw std::out_of_range("");
        }
    }

    size_t max_width_;
    size_t max_height_;

    T* pArray_{nullptr};
};

}  // namespace pipeline
