nclude <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {}
  
  // copy constr
  Array(const Array& src) : Array(src.size())
  {
      if(src.size())
          for(size_t it=0; it < src.size(); it++)
              m_array[it] = src[it];
  }
  
  // move constr
  Array(const Array&& src) : Array(src.size())
  {
      if(src.size())
          for(size_t it=0; it < src.size(); it++)
              m_array[it] = src[it];
      src.~Array();
  }

  Array& operator =(const Array& src)
  {   
      if (this == &src)
          return *this;
      
      Array tmp = src;
      delete m_array;
      m_size = tmp.size();
      m_array = new T[m_size];
      if(m_size)
          for(size_t it=0; it < m_size; it++)
              m_array[it] = tmp[it];
      else
          m_array = nullptr;
      return *this;
  }
      
  size_t size() const
  {
      return m_size;
  } 
    
  T& operator [](const size_t index) const
  {
      assert(index < m_size);
      return m_array[index];
  }

  ~Array() { delete[] m_array; }
  
private:
    size_t m_size;
    T* m_array;
};
