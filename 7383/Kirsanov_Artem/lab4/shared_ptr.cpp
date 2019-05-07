#include <iostream>
namespace stepik
{

  template <typename T>
  class shared_ptr
  {
    template <typename Y>
    friend class shared_ptr;

  public:
    explicit shared_ptr(T *ptr = 0) : ptr(ptr), count(ptr ? new long(1) : nullptr){}

    ~shared_ptr()
    {
        decr();
    }

    shared_ptr(const shared_ptr & other) : ptr(other.ptr), count(other.count)
    {
        if(count) (*count)++;
    }

    template <typename Y>
    shared_ptr(const shared_ptr<Y> & other) : ptr(other.ptr), count(other.count)
    {
        if(count) (*count)++;
    }

    shared_ptr& operator = (const shared_ptr & other)
    {
        shared_ptr tmp(other);
        swap(tmp);
        return *this;
    }

    template <typename Y>
    shared_ptr& operator = (const shared_ptr<Y> & other)
    {
        shared_ptr tmp(other);
        swap(tmp);
        return *this;
    }

    explicit operator bool() const
    {
        return ptr != nullptr;
    }

    template <typename Y>
    bool operator == (const shared_ptr<Y> &other) const
    {
        return (ptr == other.ptr);
    }

    T* get() const
    {
        return ptr;
    }

    long use_count() const
    {
        return (count ? (*count) : 0);
    }

    T& operator*() const
    {
        if(ptr) return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        std :: swap(ptr, x.ptr);
        std :: swap(count, x.count);
    }

    void reset(T *ptr = 0)
    {
        decr();
        this->ptr = ptr;
        count = ptr ? new long(1) : nullptr;
    }

  private:
    void decr(){
        if(count){
            if((*count) == 1){
                delete ptr;
                delete count;
            }
            else (*count)--;
        }
    }

    T *ptr;
    long *count;
  };
}
