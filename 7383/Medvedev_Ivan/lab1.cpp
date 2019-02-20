#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
using namespace std;

template<typename T>
class Array
{
public:
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
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
    Array(const Array &a): m_size(a.m_size), m_array(m_size ? new T[m_size]() : nullptr){
        std::copy( a.m_array, a.m_array+a.m_size, m_array);
    }
    
    Array(Array&& a): m_size(a.m_size), m_array(m_size ? new T[m_size]() : nullptr){
        a.m_array = nullptr;
        a.m_size = 0;
    }
    
    Array& operator = (Array&& a){
        T* save = m_array;
        size_t checkSize = m_size;
        try{
            m_size = a.m_size;
            m_array = a.m_array;
            destroy();
            a.m_array = nullptr;
        }
        catch(...){
            m_array = save;
            m_size = checkSize;
            throw;
        }
        return *this;
    }

    Array& operator = (const Array& a){
        unique_ptr<T[]> check(new T[a.m_size]);
        T* save = m_array;
        size_t checkSize = m_size;
        try{
            std::copy(a.m_array, a.m_array+a.m_size, check.get());
            m_size = a.m_size;
            m_array = check.release();
            delete[] save;
        }
        catch(...){
            m_array = save;
            m_size = checkSize;
            throw;
        }
        return *this;
    }
    
    void destroy(){
        if(m_array){
            delete[] m_array;
            m_size = 0;
        }
        
    }
    ~Array(){
        destroy();
    }
private:
  size_t m_size;
  T* m_array;
};
