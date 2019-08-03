#ifndef CONSTSIZEPRIORITYQUEUE_HPP
#define CONSTSIZEPRIORITYQUEUE_HPP

#include "PriorityQueue.hpp"

#include <functional>
#include <vector>

namespace sc
{
template <typename _Tp, typename _ComparatorType = std::less<_Tp>>
class ConstSizePriorityQueue : public PriorityQueue<_Tp>
{
public:
    /**
     * @brief initialize  oriented binary heap
     * @param capacity maximum number of elements
     */
    explicit ConstSizePriorityQueue(size_t capacity);

    /**
     * @brief default ctor
     */
    ConstSizePriorityQueue();

    /**
     * @brief deallocate memory
     */
    virtual ~ConstSizePriorityQueue();

    /**
     * @brief change capacity and reset priority queue
     * @param newCapacity: maximum number of elements
     */
    virtual void changeCapacity(size_t newCapacity);

    /**
     * @brief resets priority queue to clean state
     */
    virtual void resetPriorityQueue();

    /**
     * @brief insert new element
     * @param element: element to insert
     */
    virtual void push(const _Tp& element) override;

    /**
     * @brief insert new element into priority queue
     * @param newElement: new element to insert
     */
    virtual void push(_Tp&& element) override;

    /**
     * @brief remove top (imum) element
     */
    virtual void pop() override;

    /**
     * @brief return the top (imum) element without deleting it
     * @return const _Tp&: const reference to the imum element
     */
    virtual const _Tp& top() const override;

    /**
     * @brief return the number of elements in the queue
     * @return size_t
     */
    virtual size_t size() const override;

    /**
     * @brief return the maximum number of elements that can be stored in the queue
     * @return size_t
     */
    virtual size_t capacity() const;

    /**
     * @brief check if the queue is empty
     * @return bool
     */
    virtual bool empty() const override;

    // default/deleted
    ConstSizePriorityQueue(ConstSizePriorityQueue<_Tp, _ComparatorType>& rhs) = delete;
    ConstSizePriorityQueue(ConstSizePriorityQueue<_Tp, _ComparatorType>&& rhs) = default;
    virtual ConstSizePriorityQueue operator=(
        const ConstSizePriorityQueue<_Tp, _ComparatorType>& rhs) = delete;
    virtual ConstSizePriorityQueue operator=(
        const ConstSizePriorityQueue<_Tp, _ComparatorType>&& rhs) = delete;

protected:
    _ComparatorType comparator;

    /**
     * @brief promote element k if less than its parent
     * @param k: index of element to promote
     */
    virtual void swim(uint32_t k);

    /**
     * @brief demote element k if greater than its parent
     * @param k: index of element to demote
     */
    virtual void sink(uint32_t k);

    /**
     * @brief swap 2 elements
     * @param j: index of the first element
     * @param k: index of the second element
     */
    virtual void exch(uint32_t j, uint32_t k);

    // max number of elements that can be stored
    size_t capacity_ = 0;

    // position of last element
    size_t N_ = 0;

    // underlying storage container for elements in priority queue
    std::vector<_Tp> heap_;
};

template <typename _Tp, typename _ComparatorType>
ConstSizePriorityQueue<_Tp, _ComparatorType>::ConstSizePriorityQueue(size_t capacity)
    : capacity_(capacity)
{
    // binary heaps do not use element 0
    // so need an extra element in array
    heap_.resize(capacity_ + 1);
}

template <typename _Tp, typename _ComparatorType>
ConstSizePriorityQueue<_Tp, _ComparatorType>::ConstSizePriorityQueue()
{
}

template <typename _Tp, typename _ComparatorType>
ConstSizePriorityQueue<_Tp, _ComparatorType>::~ConstSizePriorityQueue()
{
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::changeCapacity(size_t newCapacity)
{
    // only need to change capacity if increasing size
    if (newCapacity > capacity_)
    {
        capacity_ = newCapacity;
        heap_.resize(capacity_ + 1);
    }

    resetPriorityQueue();
}

template <typename _Tp, typename _ComparatorType>
inline void ConstSizePriorityQueue<_Tp, _ComparatorType>::resetPriorityQueue()
{
    N_ = 0;
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::push(const _Tp& element)
{
    // make sure capacity is nonzero
    // make sure heap size is nonzero and make sure inserting current element before the last
    // element possible
    if (capacity_ != 0 && heap_.size() != 0 && N_ < capacity_)
    {
        heap_[++N_] = element;
        swim(N_);
    }
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::push(_Tp&& element)
{
    // make sure capacity is nonzero
    // make sure heap size is nonzero and make sure inserting current element before the last
    // element possible
    if (capacity_ != 0 && heap_.size() != 0 && N_ < capacity_)
    {
        heap_[++N_] = element;
        swim(N_);
    }
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::pop()
{
    // swap root element and last element
    exch(1, N_--);
    // demote root to reorder heap
    sink(1);
}

template <typename _Tp, typename _ComparatorType>
const _Tp& ConstSizePriorityQueue<_Tp, _ComparatorType>::top() const
{
    return heap_[1];
}

template <typename _Tp, typename _ComparatorType>
size_t ConstSizePriorityQueue<_Tp, _ComparatorType>::size() const
{
    return N_;
}

template <typename _Tp, typename _ComparatorType>
size_t ConstSizePriorityQueue<_Tp, _ComparatorType>::capacity() const
{
    return capacity_;
}

template <typename _Tp, typename _ComparatorType>
bool ConstSizePriorityQueue<_Tp, _ComparatorType>::empty() const
{
    return N_ == 0;
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::swim(uint32_t k)
{
    // check if we're not at root node and if child is less than parent
    // if so, swap the elements
    while (k > 1 && comparator(heap_[k], heap_[k / 2]))
    {
        exch(k, k / 2);
        k = k / 2;
    }
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::sink(uint32_t k)
{
    while (2 * k <= N_)
    {
        uint32_t j = 2 * k;
        // check if left child is greater than right child
        // if so, increment j to point to right child
        if (j < N_ && comparator(heap_[j + 1], heap_[j]))
        {
            j++;
        }
        // if parent is less than the smallest child, don't need to do anything
        if (comparator(heap_[k], heap_[j]))
        {
            break;
        }
        // swap parent and smaller child
        exch(k, j);
        k = j;
    }
}

template <typename _Tp, typename _ComparatorType>
void ConstSizePriorityQueue<_Tp, _ComparatorType>::exch(uint32_t j, uint32_t k)
{
    _Tp swap = heap_[j];
    heap_[j] = heap_[k];
    heap_[k] = swap;
}
}  // namespace sc

#endif