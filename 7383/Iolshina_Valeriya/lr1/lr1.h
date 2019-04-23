#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
    Array(const size_t size = 0) :
        m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
    {}
    
    Array(const Array &arr) :      //copy
        m_size(arr.m_size), m_array(arr.m_size ? new T[arr.m_size]() : nullptr)
    {
        try
        {
            std::copy(arr.m_array,arr.m_array+arr.size(),m_array);
        }
        catch (...)
        {
            delete[] m_array;
            throw;
        }        
    }
    
    Array(const Array&& arr) :      //move
        m_size(arr.m_size), m_array(arr.m_array) 
    {    
        arr.m_size=0;
        arr.m_array = nullptr;
    }
    
     Array& operator = (const Array &arr)    //assign
    {      
            Array tmp_arr(arr);
            m_size = tmp_arr.m_size;
            m_array = m_size ? new T[m_size]() : nullptr;
            std:: copy(tmp_arr.m_array, tmp_arr.m_array+tmp_arr.size(), m_array);

        return *this;
    }
    
    ~Array()
    {
        delete[] m_array;
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
  T* m_array;
};
