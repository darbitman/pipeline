#ifndef SHAREDQUEUE_HPP
#define SHAREDQUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <type_traits>

#include "SharedContainer.hpp"

namespace sc
{
template <typename _Tp>
class SharedQueue : public SharedContainer<_Tp>
{
  public:
    explicit SharedQueue(bool isBlocking = true) : isBlocking_(isBlocking) {}

    virtual ~SharedQueue() = default;

    virtual const _Tp& front()
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        // if this is a blocking queue, wait to be notified when when a new object is added
        if (isBlocking_)
        {
            while (queue_.empty())
            {
                cv_.wait(mlock);
            }
        }

        return queue_.front();
    }

    virtual bool empty() const
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        return queue_.empty();
    }

    virtual size_t size() const
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        return queue_.size();
    }

    virtual void push(const _Tp& value)
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        if constexpr (std::is_copy_constructible_v<_Tp>)
        {
            queue_.push(value);
        }
        else
        {
            throw std::invalid_argument("Type _Tp can't be copy constructed");
        }

        if (isBlocking_)
        {
            if (queue_.size() == 1)
            {
                cv_.notify_all();
            }
        }
    }

    virtual void push(_Tp&& value)
    {
        {
            std::unique_lock<std::mutex> mlock(mtx_);

            queue_.push(std::move(value));

            if (isBlocking_)
            {
                if (queue_.size() == 1)
                {
                    cv_.notify_all();
                }
            }
        }
    }

    template <typename... _Args>
    void emplace(_Args&&... __args)
    {
        {
            std::unique_lock<std::mutex> mlock(mtx_);

            queue_.emplace(std::forward<_Args>(__args)...);

            if (isBlocking_)
            {
                if (queue_.size() == 1)
                {
                    cv_.notify_all();
                }
            }
        }
    }

    virtual void pop()
    {
        std::unique_lock<std::mutex> mlock(mtx_);

        if (!queue_.empty())
        {
            queue_.pop();
        }
    }

  private:
    bool isBlocking_;

    mutable std::mutex mtx_;

    mutable std::condition_variable cv_;

    std::queue<_Tp> queue_;
};

}  // namespace sc
#endif
