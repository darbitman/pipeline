#pragma once

#include <atomic>
#include <memory>
#include <thread>

namespace sc
{
class ThreadRunner : protected std::thread
{
  public:
    ThreadRunner() : bThreadHasJoined_(false), bThreadIsRunning_(false), bThreadIsDetached_(false)
    {
    }

    template <typename _Callable, typename... _Args>
    ThreadRunner(_Callable&& __func, _Args&&... __args)
        : bThreadHasJoined_(false),
          bThreadIsRunning_(true),
          bThreadIsDetached_(false),
          thread(__func, __args...)
    {
    }

    ~ThreadRunner() {}

    ThreadRunner& operator=(ThreadRunner&& __t)
    {
        thread::operator=(std::forward<thread>(__t));
        bThreadIsRunning_.exchange(__t.bThreadIsRunning_);
        return *this;
    }

    // ThreadRunner& operator=(thread&& __t)
    // {
    //     thread::operator=(std::forward<thread>(__t));
    //     return *this;
    // }

    thread::id GetId() const { return thread::get_id(); }

    bool Joinable() const { return thread::joinable(); }

    void Join()
    {
        // can't join a detached thread
        if (bThreadIsDetached_)
        {
            return;
        }

        if (bThreadHasJoined_)
        {
            return;
        }
        else if (bThreadIsRunning_ && thread::joinable())
        {
            thread::join();
        }
    }

    bool Detach()
    {
        if (bThreadIsDetached_)
        {
            return false;
        }
        else
        {
            thread::detach();
            bThreadIsDetached_ = true;
            return true;
        }
    }

    thread::native_handle_type NativeHandle()
    {
        if (bThreadIsRunning_ && !bThreadIsDetached_)
        {
            return thread::native_handle();
        }
        else
        {
            return 0;
        }
    }

    inline static auto HardwareConcurrency() { return thread::hardware_concurrency(); }

    bool HasJoined() const { return bThreadHasJoined_; }

    bool IsDetached() const { return bThreadIsDetached_; }

  private:
    std::atomic<bool> bThreadHasJoined_;

    std::atomic<bool> bThreadIsRunning_;

    std::atomic<bool> bThreadIsDetached_;
};
}  // namespace sc
