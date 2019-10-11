#pragma once

#include <stdexcept>

namespace pipeline
{
template <typename T>
class Array1D
{
  public:
    Array1D()
        : capacity_(1),
          currentIndex_(0),
          pArray_(reinterpret_cast<T*>(::operator new(sizeof(T) * capacity_)))
    {
    }

    Array1D(size_t n)
        : capacity_(n),
          currentIndex_(0),
          pArray_(reinterpret_cast<T*>(::operator new(sizeof(T) * capacity_)))
    {
    }

    Array1D(size_t n, const T& initValue) : capacity_(n), currentIndex_(0), pArray_(nullptr)
    {
        //
    }

    Array1D(size_t capacity, size_t size, T* pArray) : ownsPointer_(false)
    {
        //
    }

    Array1D(Array1D&& other) = default;

    ~Array1D()
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

    class const_iterator
    {
      public:
        const_iterator() noexcept : pObject_(nullptr) {}

        const_iterator(T* pObject) noexcept : pObject_(pObject) {}

        const_iterator(const const_iterator& other) noexcept : pObject_(other.pObject_) {}

        ~const_iterator() = default;

        const T& operator*() const noexcept { return *pObject_; }

        const_iterator& operator++() noexcept
        {
            ++pObject_;
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            const_iterator oldIteratorToReturn(*this);
            ++pObject_;
            return oldIteratorToReturn;
        }

        bool operator!=(const const_iterator& other) const noexcept
        {
            return pObject_ != other.pObject_;
        }

      private:
        T* pObject_;
    };

    iterator begin() noexcept { return iterator(pArray_); }
    const_iterator begin() const noexcept { return const_iterator(pArray_); }
    const_iterator cbegin() const noexcept { return const_iterator(pArray_); }
    iterator end() noexcept { return iterator(pArray_ + currentIndex_); }
    const_iterator end() const noexcept { return iterator(pArray_ + currentIndex_); }
    const_iterator cend() const noexcept { return iterator(pArray_ + currentIndex_); }

    size_t capacity() const noexcept { return capacity_; }

    size_t size() const noexcept { return currentIndex_; }

    bool empty() const noexcept { return currentIndex_ == (size_t)0; }

    T& at(size_t index)
    {
        VerifyDimensionAccess(index);
        return pArray_[index];
    }

    const T& at(size_t index) const
    {
        VerifyDimensionAccess(index);
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
        T* pObject = &pArray_[currentIndex_++];

        // placement new. Construct T at memory pointed to by pObject
        new (pObject) T(std::forward<_Args>(__args)...);
    }

    void push_back(const T& object) { emplace_back(object); }

    void push_back(T&& object) { emplace_back(std::move(object)); }

  private:
    void VerifyDimensionAccess(size_t index)
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
