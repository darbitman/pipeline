

template <typename T>
class ArrayAccessor1D
{
  public:
    ArrayAccessor1D(T* pArray, size_t size) : pArray_(pArray), size_(size) {}

    ~ArrayAccessor1D() = default;

    void setBasePointer(T* pArray) { pArray_ = pArray_; }

    T& operator()(size_t index);

    T& operator[](size_t index) { return at(index); }

    const T& operator[](size_t index) const { return at(index); }

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

  private:
    void VerifyDimensionAccess(size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("");
        }
    }

    size_t size_;

    T* pArray_{nullptr};
};
