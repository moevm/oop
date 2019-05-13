#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <algorithm>
#include <iostream>

namespace stepik
{
template <typename T>
class shared_ptr
{
    struct Pointer
    {
        T* value;
        size_t count;
    };

    template <typename U>
    friend class shared_ptr;

public:
  explicit shared_ptr(T *ptr = nullptr)
  {
      if(ptr)
      {
          p = new Pointer;
          p->value = ptr;
          p->count = 1;
      }
      else
          p = nullptr;
  }

  ~shared_ptr()
  {
      if(p)
      {
          if(p->count == 1)
          {
              delete p->value;
              delete p;
          }
          else
              --(p->count);
      }
  }

  shared_ptr(const shared_ptr & other)
      : p(other.p)
  {
      if(p)
          ++(p->count);
  }

  shared_ptr& operator=(const shared_ptr & other)
  {
      if(p != other.p)
      {
          shared_ptr tmp(other);
          swap(tmp);
      }

      return *this;
  }

  explicit operator bool() const
  { return p != nullptr; }

  T* get() const
  {
      if(!p)
          return nullptr;

      return p->value;
  }

  long use_count() const
  {
      if(!p)
          return 0;

      return p->count;
  }

  T& operator*() const
  {
      if(p)
          return *(p->value);
  }

  T* operator->() const
  {
      if(!p)
          return nullptr;

      return p->value;
  }

  void swap(shared_ptr& x) noexcept
  { std::swap(p, x.p); }

  void reset(T *ptr = 0)
  {
      shared_ptr tmp(ptr);
      swap(tmp);
  }

  template <typename U>
  shared_ptr(const shared_ptr<U> & other)
  {
      p = reinterpret_cast<shared_ptr::Pointer*>(other.p);
      if(p)
          ++(p->count);
  }

  template <typename U>
  shared_ptr& operator=(const shared_ptr<U> & other)
  {
      shared_ptr tmp(other);
      swap(tmp);
  }

private:
  // data members
  Pointer* p;
};

  //cmp:
  template <class T, class U>
  bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
  {
      U* l = dynamic_cast<U*>(lhs.get());
      if(!l){
          T* r = dynamic_cast<T*>(rhs.get());
          return lhs.get() == r;
      }

      return l == rhs.get();
  }

  template <class T, class U>
  bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
  { return !(lhs == rhs); }

  template <class T, class U>
  bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
  {
      U* l = dynamic_cast<U*>(lhs.get());
      if(!l){
          T* r = dynamic_cast<T*>(rhs.get());
          return lhs.get() < r;
      }

      return l < rhs.get();
  }

  template <class T, class U>
  bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
  { return !(lhs < rhs) && (lhs != rhs); }

  template <class T, class U>
  bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
  { return !(lhs > rhs); }

  template <class T, class U>
  bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
  { return !(lhs < rhs); }

} // namespace stepik

#endif // SHARED_PTR_H
