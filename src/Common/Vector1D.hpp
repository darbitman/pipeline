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

    Vector1D(size_t capacity, size_t size, T* pArray) : ownsPointer_(false)
    {
        //
    }

    Vector1D(Vector1D&& other) = default;

    ~Vector1D()
    {
        if (ownsPointer_)
        {
            DestructAndFreeCurrentMemory();
        }
    }

    class iterator
    {
      public:
        iterator() noexcept : pObject_(nullptr) {}

        iterator(T* pObject) noexcept : pObject_(pObject) {}

        iterator(const iterator& other) noexcept : pObject_(other.pObject_) {}

        ~iterator() = default;

        T& operator*() const noexcept { return *pObject_; }

        iterator& operator++() noexcept
        {
            ++pObject_;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            iterator oldIteratorToReturn(*this);
            ++pObject_;
            return oldIteratorToReturn;
        }

        bool operator!=(const iterator& other) const noexcept { return pObject_ != other.pObject_; }

      private:
        T* pObject_;
    };

    iterator begin() const noexcept { return iterator(pArray_); }

    iterator end() const noexcept { return iterator(pArray_ + currentIndex_); }

    size_t capacity() const noexcept { return capacity_; }

    size_t size() const noexcept { return currentIndex_; }

    T& at(size_t index)
    {
        VerifyAcces(index);
        return pArray_[index];
    }

    const T& at(size_t index) const
    {
        VerifyAcces(index);
        return pArray_[index];
    }

    template <typename... _Args>
    void emplace_back(_Args&&... __args)
    {
        // check if at capacity
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
        }

        DestructAndFreeCurrentMemory();

        // update pointer and capacity
        pArray_ = pNewArray;
        capacity_ = newCapacity;
    }

    void DestructAndFreeCurrentMemory()
    {
        for (size_t i = 0; i < currentIndex_; ++i)
        {
            // explicitly need to call destructor since placement new was used
            (pArray_ + i)->~T();
        }

        // free the memory
        ::operator delete(pArray_);
    }

    size_t capacity_;

    size_t currentIndex_;

    bool ownsPointer_{true};

    T* pArray_{nullptr};
};

}  // namespace pipeline
