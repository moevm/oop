#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

#ifndef ARRAY_H
#define ARRAY_H

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
  ~Array(){ destroy(); }

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }


    Array(const Array &obj)
        : m_size(obj.m_size)
        , m_array(m_size ? new T[m_size]() : nullptr)
    {
            std::copy(obj.m_array, obj.m_array + obj.m_size, m_array);
    }

    Array& operator = (const Array& obj)
    {
        try{
            Array res(obj.m_size);
            std::copy(obj.m_array, obj.m_array + obj.m_size, res.m_array);
            m_size = res.m_size;
            m_array = new T[m_size]();
            std::copy(res.m_array, res.m_array + res.m_size, m_array);
        }
        catch(...){
            throw;
        }
        return *this;
        
    }


    Array(Array && obj)
    :    m_size(obj.size)
    ,    m_array(m_size ? new T[m_size]() : nullptr)
    {
        std::copy(obj.m_array, obj.m_array + obj.m_size, m_array);
        delete[] obj.m_array;
        obj.m_array = nullptr;
        obj.m_size = 0;
    }

private:
        void destroy()
        {
            if(m_array)
                delete[] m_array;
            m_array = nullptr;
            m_size = 0;
        }
  size_t m_size;
  T* m_array;
};

#endif