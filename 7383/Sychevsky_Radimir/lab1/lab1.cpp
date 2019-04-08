#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
    Array(const size_t size = 0): 
      m_size(size), 
      m_array(m_size ? new T[m_size]() : nullptr)
    {}
    // (copy) constructor
    Array(const Array& arr):
        m_size(arr.m_size),
        m_array(m_size ? new T[m_size]() : nullptr)
    {
        if (this->m_array != nullptr && arr.m_array != nullptr)
            std::copy(arr.m_array, arr.m_array + arr.m_size, this->m_array);    
    }
    
    //(move) constructor
    Array(Array&& arr):
        m_size(arr.m_size),
        m_array(arr.m_array)
    {
        arr.m_size = 0;
        arr.m_array = nullptr;
    }
    
    Array& operator = (const Array &arr)
    {
        if(this == &arr)
            return *this;
        Array tmp(arr.m_size);
        try{
            tmp.m_size = arr.m_size;
            for(int i = 0; i < arr.m_size; i++)
                tmp.m_array[i] = arr.m_array[i];
            m_size = tmp.m_size;
            if(m_array)
                delete [] m_array;
            m_array = tmp.m_array;
            tmp.m_array = nullptr;
        }
        catch(...){
            delete[] tmp.m_array;
            tmp.m_array = nullptr;
            throw;
        }
        return *this;
    }
    
    ~Array()
    {
        delete [] m_array;
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