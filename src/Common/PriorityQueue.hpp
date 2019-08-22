#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include "QueueInterface.hpp"

#include <functional>
#include <vector>

namespace sc
{
template <typename _Tp, typename _ComparatorType = std::less<_Tp>>
class PriorityQueue : public QueueInterface<_Tp>
{
  public:
    /**
     * @brief initialize priority queue
     * @param initial capacity of internal store
     */
    explicit PriorityQueue(size_t initialCapacity) : N_(0)
    {
        // binary heaps do not use element 0
        // so need an extra element in array
        heap_.reserve(initialCapacity + 1);
        heap_.push_back(0);
    }

    /**
     * @brief default ctor
     */
    PriorityQueue() : N_(0)
    {
        // first element is unused
        heap_.push_back(0);
    }

    /**
     * @brief deallocate memory
     */
    virtual ~PriorityQueue() = default;

    /**
     * @brief resets priority queue to clean state
     */
    virtual void resetPriorityQueue() { N_ = 0; }

    /**
     * @brief insert new element
     * @param element: element to insert
     */
    virtual void push(const _Tp& element) override
    {
        if constexpr (std::is_copy_constructible_v<_Tp>)
        {
            // if the heap_ is at capacity
            // N_ is the index while size() returns the number of elements which will always be one
            // more than the index, need to subtract 1
            if (N_ == (heap_.size() - 1))
            {
                // heap_.push_back(element);
                ++N_;
            }
            else
            {
                // heap_[++N_] = element;
            }

            swim(N_);
        }
        else
        {
            throw std::invalid_argument("Type _Tp can't be copy constructed");
        }
    }

    /**
     * @brief insert new element into priority queue
     * @param newElement: new element to insert
     */
    virtual void push(_Tp&& element) override
    {
        // if the heap_ is at capacity
        // N_ is the index while size() returns the number of elements which will always be one more
        // than the index, need to subtract 1
        if (N_ == (heap_.size() - 1))
        {
            heap_.push_back(std::forward<_Tp>(element));
            ++N_;
        }
        else
        {
            heap_[++N_] = std::forward<_Tp>(element);
        }

        swim(N_);
    }

    /**
     * @brief remove top (imum) element
     */
    virtual void pop() override
    {
        // swap root element and last element
        exch(1, N_--);
        // demote root to reorder heap
        sink(1);
    }

    /**
     * @brief return the top (imum) element without deleting it
     * @return const _Tp&: const reference to the imum element
     */
    virtual const _Tp& top() const override { return heap_[1]; }

    /**
     * @brief return the number of elements in the queue
     * @return size_t
     */
    virtual size_t size() const override { return N_; }

    /**
     * @brief check if the queue is empty
     * @return bool
     */
    virtual bool empty() const override { return N_ == 0; }

    // default/deleted
    PriorityQueue(PriorityQueue<_Tp, _ComparatorType>& rhs) = delete;
    PriorityQueue(PriorityQueue<_Tp, _ComparatorType>&& rhs) = default;
    PriorityQueue operator=(const PriorityQueue<_Tp, _ComparatorType>& rhs) = delete;
    PriorityQueue operator=(const PriorityQueue<_Tp, _ComparatorType>&& rhs) = delete;

  protected:
    _ComparatorType comparator;

    /**
     * @brief promote element k if less than its parent
     * @param k: index of element to promote
     */
    virtual void swim(uint32_t k)
    {
        // check if we're not at root node and if child is less than parent
        // if so, swap the elements
        while (k > 1 && comparator(heap_[k], heap_[k / 2]))
        {
            exch(k, k / 2);
            k = k / 2;
        }
    }

    /**
     * @brief demote element k if greater than its parent
     * @param k: index of element to demote
     */
    virtual void sink(uint32_t k)
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

    /**
     * @brief swap 2 elements
     * @param j: index of the first element
     * @param k: index of the second element
     */
    virtual void exch(uint32_t j, uint32_t k)
    {
        _Tp swap = std::move(heap_[j]);
        heap_[j] = std::move(heap_[k]);
        heap_[k] = std::move(swap);
    }

    // position of last element
    size_t N_;

    // underlying storage container for elements in priority queue
    std::vector<_Tp> heap_;
};

}  // namespace sc

#endif