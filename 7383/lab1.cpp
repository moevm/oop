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
  
    // (copy) constructor
    Array(const Array& arr)
      : m_size(arr.m_size)
      , m_array(m_size ? new T[m_size]() : nullptr)
    {
       try
      {
        std::copy(arr.m_array, arr.m_array + m_size, m_array); 
      }
      catch(...)
      {
        this->~Array();
        throw;
      }
    }
  
    // (move) constructor
    Array(Array&& arr)
      : m_size(arr.m_size)
      , m_array(arr.m_array)
    {
        arr.m_size = 0;
        arr.m_array = nullptr;
    }
  
   

    // operator =
    Array &operator=(Array arr)
    {
      swap(arr); 
      return *this;
    } 
  
    void swap(Array &arr) 
    {
      using std::swap;
  
      swap(m_size, arr.m_size);
      swap(m_array, arr.m_array);
    }
  
   ~Array()
    {
        delete[] m_array;
    }
  
    size_t size() const
    {
      return m_size;
    }
  
    T* get_array() const
    {
        return m_array;
    }
  
    T& operator [](const size_t index)
    {
      assert(index < m_size);
  
      return m_array[index];
    }
  
    
  
  private:
    size_t m_size;
    T* m_array;
  };