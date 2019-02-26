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
    
  ~Array () {
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
    
  Array(Array && other)
      : m_array(other.m_array)
      , m_size(other.m_size)
  {
      other.m_array = NULL;
      other.m_size = 0;
  }
    
  Array(const Array& other)
      : m_size(other.m_size)
      , m_array(new T[m_size])
  { 
      std::copy(other.m_array, other.m_array + m_size, m_array);
  }
    
  Array& operator=(Array& other)
  {
      std::unique_ptr<T[]> ptr(new T[other.m_size]);
      std::copy(other.m_array, other.m_array + other.m_size, ptr.get());
      delete[] m_array;
      m_size = other.m_size;
      m_array = ptr.release();
      return *this;
  }

private:
  size_t m_size;
  T* m_array;
};
/*#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
#include <memory>

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
    
  ~Array () {
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
    
  Array(Array && other)
      : m_array(other.m_array)
      , m_size(other.m_size)
  {
  	  std::cout << "Move Construct";
      other.m_array = NULL;
      other.m_size = 0;
  }
    
  Array(const Array& other) 
      : m_size(other.m_size)
      , m_array(new T[m_size])
  { 
  	  std::cout << "Copy Construct";
      std::copy(other.m_array, other.m_array + m_size, m_array);
  }
    
  Array& operator=(Array& other)
  {
  	  std::cout << "Operator";
      std::unique_ptr<T[]> ptr(new T[other.m_size]);
      std::copy(other.m_array, other.m_array + other.m_size, ptr.get());
      delete[] m_array;
      m_size = other.m_size;
      m_array = ptr.release();
      return *this;
  }

private:
  size_t m_size;
  T* m_array;
};
int main() {
	Array <int> a(1);
	Array <int> b(a);
	Array <int> c(std::move(a));
	b = c;
	//Array <int> b = a;
	
	// your code goes here
	return 0;
}*/
