#ifndef SHAREDPRIORITYQUEUEADAPTER_HPP
#define SHAREDPRIORITYQUEUEADAPTER_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

#include "PriorityQueue.hpp"
#include "SharedContainer.hpp"

namespace sc
{
template <typename _Tp, typename _ComparatorType = std::less<_Tp>>
class SharedPriorityQueueAdapter : public SharedContainer<_Tp>
{
  public:
    explicit SharedPriorityQueueAdapter(
        std::unique_ptr<PriorityQueue<_Tp, _ComparatorType>>& pConstSizePQ, bool isBlocking = true)
        : isBlocking(isBlocking), pConstSizeMinPQ_(std::move(pConstSizePQ))
    {
    }

    explicit SharedPriorityQueueAdapter(
        std::unique_ptr<PriorityQueue<_Tp, _ComparatorType>>&& pConstSizePQ, bool isBlocking = true)
        : isBlocking(isBlocking), pConstSizeMinPQ_(std::move(pConstSizePQ))
    {
    }

    virtual ~SharedPriorityQueueAdapter() = default;

    virtual const _Tp& front() override
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

    virtual bool empty() const override
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        return pConstSizeMinPQ_->empty();
    }

    virtual size_t size() const override
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        return pConstSizeMinPQ_->size();
    }

    virtual void push(const _Tp& value) override
    {
        if constexpr (std::is_copy_constructible_v<_Tp>)
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
        else
        {
            throw std::invalid_argument("Type _Tp can't be copy constructed");
        }
    }

    virtual void push(_Tp&& value) override
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        pConstSizeMinPQ_->push(std::forward<_Tp>(value));

        if (isBlocking)
        {
            if (pConstSizeMinPQ_->size() == 1)
            {
                cv_.notify_all();
            }
        }
    }

    virtual void pop() override
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        if (!pConstSizeMinPQ_->empty())
        {
            pConstSizeMinPQ_->pop();
        }
    }

  private:
    bool isBlocking;

    mutable std::mutex mtx_;

    mutable std::condition_variable cv_;

    std::shared_ptr<PriorityQueue<_Tp, _ComparatorType>> pConstSizeMinPQ_;
};

}  // namespace sc

#endif
