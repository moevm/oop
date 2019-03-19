#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }

    
    Array(const Array<T> &t): m_size(t.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr){
        std::copy(t.m_array.get(),t.m_array.get()+m_size,m_array.get());
    }
    
    Array(const Array<T>&& t)
        : m_size(std::move(t.m_size))
        , m_array(std::move(t.m_array))
    {
    }
    
    Array<T> & operator=(const Array<T> &t){
        if(this != &t){
        std::unique_ptr<T[]> new_m(new T[t.m_size]);
        std::copy(t.m_array.get(), t.m_array.get() + t.m_size, new_m.get());
        m_size = t.m_size;
        m_array.reset(new_m.release());
        }
        return *this;
   
    }
  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

private:
  size_t m_size;
  std::unique_ptr<T[]> m_array;
};
