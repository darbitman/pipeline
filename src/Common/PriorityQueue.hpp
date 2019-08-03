#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <cstddef>
#include <cstdint>

namespace sc
{
template <typename _Tp>
class PriorityQueue
{
public:
    /**
     * @brief dtor
     */
    virtual ~PriorityQueue() {}

    /**
     * @brief insert new element into priority queue
     * @param element: new element to insert
     */
    virtual void push(const _Tp& element) = 0;

    /**
     * @brief insert new element into priority queue
     * @param element: new element to insert
     */
    virtual void push(_Tp&& element) = 0;

    /**
     * @brief remove top element
     */
    virtual void pop() = 0;

    /**
     * @brief return the top (minimum) element without deleting it
     * @return const _Tp&: const reference to the minimum element
     */
    virtual const _Tp& top() const = 0;

    /**
     * @brief return the number of elements in the queue
     * @return size_t
     */
    virtual size_t size() const = 0;

    /**
     * @brief check if the queue is empty
     * @return bool returns true if queue is empty
     */
    virtual bool empty() const = 0;
};
}  // namespace sc

#endif