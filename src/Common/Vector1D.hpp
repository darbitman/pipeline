#pragma once

#include <stdexcept>

namespace pipeline
{
template <typename T>
class Vector1D
{
  public:
    Vector1D()
        : capacity_(1),
          currentIndex_(0),
          pArray_(reinterpret_cast<T*>(::operator new(sizeof(T) * capacity_)))
    {
    }

    Vector1D(size_t n)
        : capacity_(n),
          currentIndex_(0),
          pArray_(reinterpret_cast<T*>(::operator new(sizeof(T) * capacity_)))
    {
    }

    Vector1D(size_t n, const T& initValue) : capacity_(n), currentIndex_(0), pArray_(nullptr)
    {
        //
    }

    Vector1D(size_t capacity, size_t currentIndex, T* pArray) : ownsPointer_(false)
    {
        //
    }

    Vector1D(Vector1D&& other) = default;

    ~Vector1D()
    {
        if (ownsPointer_)
        {
            for (size_t i = 0; i < currentIndex_; ++i)
            {
                (pArray_ + i)->~T();
            }

            ::operator delete(pArray_);
        }
    }

    T& at(size_t index)
    {
        VerifyAcces(index);
        return pArray_[index];
    }

    size_t capacity() const noexcept { return capacity_; }

    const T& at(size_t index) const
    {
        VerifyAcces(index);
        return pArray_[index];
    }

    template <typename... _Args>
    void emplace_back(_Args&&... __args)
    {
        // check for capacity
        if (currentIndex_ == capacity_)
        {
            EnlargeArray();
        }
        auto pObject = &pArray_[currentIndex_++];
        new (pObject) T(std::forward<_Args>(__args)...);
    }

    void push_back(const T& object) { emplace_back(object); }

    void push_back(T&& object) { emplace_back(std::move(object)); }

  private:
    void VerifyAcces(size_t index)
    {
        if (index >= currentIndex_)
        {
            throw std::out_of_range("");
        }
    }

    void EnlargeArray()
    {
        // create new array
        size_t newCapacity = capacity_ * 2;
        T* pNewArray = reinterpret_cast<T*>(::operator new(sizeof(T) * newCapacity));

        // move objects from old array to new one
        for (size_t i = 0; i < currentIndex_; ++i)
        {
            new (pNewArray + i) T(std::move(*(pArray_ + i)));

            // explicitly need to call destructor since placement new was used
            (pArray_ + i)->~T();
        }

        // free the memory
        ::operator delete(pArray_);

        // update pointer and capacity
        pArray_ = pNewArray;
        capacity_ = newCapacity;
    }

    size_t capacity_;

    size_t currentIndex_;

    bool ownsPointer_{true};

    T* pArray_{nullptr};
};

}  // namespace pipeline
