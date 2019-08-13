#ifndef SHAREDCONSTSIZEPQADAPTER_HPP
#define SHAREDCONSTSIZEPQADAPTER_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

#include "PriorityQueue.hpp"
#include "SharedContainer.hpp"

namespace sc
{
template <typename _Tp, typename _ComparatorType = std::less<_Tp>>
class SharedConstSizePQAdapter : public SharedContainer<_Tp>
{
   public:
    explicit SharedConstSizePQAdapter(
        std::shared_ptr<PriorityQueue<_Tp, _ComparatorType>>
            pConstSizePQ,
        bool isBlocking = true);

    virtual ~SharedConstSizePQAdapter();

    virtual const _Tp& front() override;

    virtual bool empty() const override;

    virtual size_t size() const override;

    virtual void push(const _Tp& value) override;

    virtual void push(_Tp&& value) override;

    virtual void pop() override;

   private:
    bool isBlocking;

    mutable std::mutex mtx_;

    mutable std::condition_variable cv_;

    std::shared_ptr<PriorityQueue<_Tp, _ComparatorType>>
        pConstSizeMinPQ_;
};

template <typename _Tp, typename _ComparatorType>
SharedConstSizePQAdapter<_Tp, _ComparatorType>::SharedConstSizePQAdapter(
    std::shared_ptr<PriorityQueue<_Tp, _ComparatorType>> pConstSizePQ,
    bool isBlocking)
    : isBlocking(isBlocking), pConstSizeMinPQ_(pConstSizePQ)
{
}

template <typename _Tp, typename _ComparatorType>
SharedConstSizePQAdapter<_Tp, _ComparatorType>::~SharedConstSizePQAdapter()
{
}

template <typename _Tp, typename _ComparatorType>
const _Tp& SharedConstSizePQAdapter<_Tp, _ComparatorType>::front()
{
    std::unique_lock<std::mutex> mlock(mtx_);

    // if this is a blocking queue, wait to be notified when when a new object
    // is added
    if (isBlocking)
    {
        while (pConstSizeMinPQ_->empty())
        {
            cv_.wait(mlock);
        }
    }
    return pConstSizeMinPQ_->top();
}

template <typename _Tp, typename _ComparatorType>
bool SharedConstSizePQAdapter<_Tp, _ComparatorType>::empty() const
{
    std::unique_lock<std::mutex> mlock(mtx_);

    return pConstSizeMinPQ_->empty();
}

template <typename _Tp, typename _ComparatorType>
size_t SharedConstSizePQAdapter<_Tp, _ComparatorType>::size() const
{
    std::unique_lock<std::mutex> mlock(mtx_);

    return pConstSizeMinPQ_->size();
}

template <typename _Tp, typename _ComparatorType>
void SharedConstSizePQAdapter<_Tp, _ComparatorType>::push(const _Tp& value)
{
    std::unique_lock<std::mutex> mlock(mtx_);

    pConstSizeMinPQ_->push(value);

    if (isBlocking)
    {
        if (pConstSizeMinPQ_->size() == 1)
        {
            cv_.notify_all();
        }
    }
}

template <typename _Tp, typename _ComparatorType>
void SharedConstSizePQAdapter<_Tp, _ComparatorType>::push(_Tp&& value)
{
    std::unique_lock<std::mutex> mlock(mtx_);

    pConstSizeMinPQ_->push(value);

    if (isBlocking)
    {
        if (pConstSizeMinPQ_->size() == 1)
        {
            cv_.notify_all();
        }
    }
}

template <typename _Tp, typename _ComparatorType>
void SharedConstSizePQAdapter<_Tp, _ComparatorType>::pop()
{
    std::unique_lock<std::mutex> mlock(mtx_);

    if (!pConstSizeMinPQ_->empty())
    {
        pConstSizeMinPQ_->pop();
    }
}

}  // namespace sc

#endif
