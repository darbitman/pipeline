#ifndef SHAREDCONTAINER_HPP
#define SHAREDCONTAINER_HPP

namespace sc
{
template <typename _Tp>
class SharedContainer
{
  public:
    virtual ~SharedContainer() {}

    virtual const _Tp& front() const = 0;

    virtual _Tp& front() = 0;

    virtual bool empty() const = 0;

    virtual size_t size() const = 0;

    virtual void push(const _Tp& value) = 0;

    virtual void push(_Tp&& value) = 0;

    virtual void pop() = 0;
};

}  // namespace sc

#endif
