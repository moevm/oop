#include <iostream>
#include <algorithm>
using namespace std;
namespace stepik{
template <typename T>
class shared_ptr
{
public:
  explicit shared_ptr(T *ptr = 0)
  {
    my_ptr = ptr;
    i = new long;
    *i = 1;
  }

  ~shared_ptr()
  {
        if ((*i) > 0)
            --(*i);
        if ((*i) == 0){
            delete my_ptr;
            delete i;
        }
  }

  shared_ptr(const shared_ptr & other)
  {
    my_ptr = other.my_ptr;
    i = other.i;
    ++(*i);
  }

  template<typename Derived>
  shared_ptr(const shared_ptr<Derived> & other){
      this->my_ptr = other.my_ptr;
      this->i = other.i;
      ++(*i);
  }

  shared_ptr& operator=(const shared_ptr & other)
  {
    if (this != &other){
        this->~shared_ptr();
        my_ptr = other.my_ptr;
        i = other.i;
        ++(*i);
    }
    return *this;
  }
  template<typename Derived>
  shared_ptr& operator=(const shared_ptr<Derived> & other)
  {
    if ((void*)my_ptr != (void*)&other.my_ptr){
        this->~shared_ptr();
        my_ptr = other.my_ptr;
        i = other.i;
        ++(*i);
    }
    return *this;
  }

  explicit operator bool() const
  {
    return my_ptr != nullptr;
  }

  template <typename Derived>
     bool operator==(const shared_ptr<Derived> & other) const
     {
       return my_ptr == other.my_ptr;
     }

  T* get() const
  {
    return my_ptr;
  }

  long use_count() const
  {
    return my_ptr == nullptr ? 0 : (*i);
  }

  T& operator*() const
  {
    return *my_ptr;
  }

  T* operator->() const
  {
    return my_ptr;
  }

  void swap(shared_ptr& x) noexcept
  {
    swap(my_ptr,x.my_ptr);
    swap(i,x.i);
  }

  void reset(T *ptr = 0)
  {
    this->~shared_ptr();
    my_ptr = ptr;
    i = new long;
  }

private:
    T* my_ptr;
    long* i;
    template <typename Derived>
    friend class shared_ptr;
};
} // namespace stepik
int main()
{
    stepik::shared_ptr<int>(t);
    return 0;
}
