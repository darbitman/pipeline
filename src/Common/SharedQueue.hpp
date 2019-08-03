#ifndef SHAREDQUEUE_HPP
#define SHAREDQUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

#include "SharedContainer.hpp"

namespace sc
{
template <typename _Tp>
class SharedQueue : public SharedContainer<_Tp>
{
public:
    explicit SharedQueue(bool isBlocking = true);

    virtual ~SharedQueue();

    virtual const _Tp& front() override;

    virtual bool empty() const override;

    virtual size_t size() const override;

    virtual void push(const _Tp& value) override;

    virtual void push(_Tp&& value) override;

    template <typename... _Args>
    void emplace(_Args&&... __args);

    virtual void pop() override;

private:
    bool isBlocking_;

    mutable std::mutex mtx_;

    mutable std::condition_variable cv_;

    std::queue<_Tp> queue_;
};

template <typename _Tp>
SharedQueue<_Tp>::SharedQueue(bool isBlocking) : isBlocking_(isBlocking)
{
}

template <typename _Tp>
SharedQueue<_Tp>::~SharedQueue()
{
}

template <typename _Tp>
const _Tp& SharedQueue<_Tp>::front()
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

template <typename _Tp>
bool SharedQueue<_Tp>::empty() const
{
    std::unique_lock<std::mutex> mlock(mtx_);
    
    return queue_.empty();
}

template <typename _Tp>
size_t SharedQueue<_Tp>::size() const
{
    std::unique_lock<std::mutex> mlock(mtx_);

    return queue_.size();
}

template <typename _Tp>
void SharedQueue<_Tp>::push(const _Tp& value)
{
    std::unique_lock<std::mutex> mlock(mtx_);

    queue_.push(value);

    if (isBlocking_)
    {
        if (queue_.size() == 1)
        {
            cv_.notify_all();
        }
    }
}

template <typename _Tp>
void SharedQueue<_Tp>::push(_Tp&& value)
{
    std::unique_lock<std::mutex> mlock(mtx_);

    queue_.push(value);

    if (isBlocking_)
    {
        if (queue_.size() == 1)
        {
            cv_.notify_all();
        }
    }
}

template <typename _Tp>
template <typename... _Args>
void SharedQueue<_Tp>::emplace(_Args&&... __args)
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

template <typename _Tp>
void SharedQueue<_Tp>::pop()
{
    std::unique_lock<std::mutex> mlock(mtx_);

    if (!queue_.empty())
    {
        queue_.pop();
    }
}

}  // namespace sc
#endif
