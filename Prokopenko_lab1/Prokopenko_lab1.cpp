#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
using namespace std;

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
  Array(const Array& cop) : Array(cop.size()){
          copy(cop.m_array, cop.m_array+cop.size(), m_array);
  }
  Array(Array&& mov) : m_size(mov.m_size), m_array(mov.m_array){
      mov.m_array = nullptr;
  }
  Array& operator= (const Array& cop){
      Array tmp(cop);
      m_size = tmp.size();
      m_array = m_size ? new T[m_size]() : nullptr;
      copy(tmp.m_array, tmp.m_array+tmp.size(), m_array);
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
  ~Array(){
      delete[] m_array;
  }
private:
  size_t m_size;
  T* m_array;
};
