#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <algorithm>
#include <iostream>


namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0) : ptr(ptr)
    {
        counter = nullptr;
        if (ptr)
        {
            counter = new long;
            (*counter) = 1;
        }
    }

    ~shared_ptr()
    {
        clear();
    }

    shared_ptr(const shared_ptr & other) : ptr(other.ptr), counter(other.counter)
    {
        if (counter)
            (*counter)++;
    }

    template<typename Derived>
    shared_ptr(const shared_ptr<Derived> & other)
    {
        ptr = other.ptr;
        counter = other.counter;
        if (counter)
            (*counter)++;
    }


    shared_ptr& operator=(const shared_ptr & other)
    {
        if (this == &other)
            return *this;

        clear();
        ptr = other.ptr;
        counter = other.counter;
        if (counter)
            (*counter)++;
        return *this;
    }

    template<typename Derived>
    shared_ptr& operator=(const shared_ptr<Derived> & other)
    {
        if ((void*)this == (void*)&other)
            return *this;

        clear();
        ptr = other.ptr;
        counter = other.counter;
        if (counter)
            (*counter)++;
        return *this;
    }

    template<typename Derived>
    bool operator==(const shared_ptr<Derived> & other) const
    {
        return ptr == other.ptr;
    }

    explicit operator bool() const
    {
        return !(ptr == nullptr);
    }

    T* get() const
    {
        return ptr;
    }

    long use_count() const
    {
        if (counter)
            return *counter;
        return 0;
    }

    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(ptr, x.ptr);
        std::swap(counter, x.counter);
    }

    void reset(T *ptr = 0)
    {
        clear();
        this->ptr = ptr;
        if (ptr)
        {
            counter = new long;
            *counter = 1;
        }
    }

  private:
    void clear()
    {
        if (counter && *counter > 0)
        {
            (*counter)--;
        }
        if (counter && *counter == 0)
        {
            delete ptr;
            delete counter;
        }
        ptr = nullptr;
        counter = nullptr;
    }

  private:
    template<typename Derived>
    friend class shared_ptr;

        T* ptr;
        long* counter;
  };
} // namespace stepik

#endif // SHARED_PTR_H
