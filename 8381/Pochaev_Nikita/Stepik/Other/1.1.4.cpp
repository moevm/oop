#include <cassert>
#include <algorithm>    // std::copy
#include <cstddef>      // size_t
#include <utility>      // std::swap
#include <iostream>
#include <memory>

template<typename T>
class Array
{
public:
  explicit Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr) { }
    
  Array(const Array& arr) : m_size(arr.m_size), m_array(m_size ? new T[m_size]() : nullptr)
  {
          std::copy(arr.m_array.get(), arr.m_array.get() + m_size, m_array.get());
  }
    
  Array(Array &&arr)  noexcept : m_size(std::move(arr.m_size)), m_array(std::move(arr.m_array))
  {
  }

  ~Array() noexcept = default;

  Array& operator= (Array arr)
  {
        std::swap(this->m_size, arr.m_size);
        std::swap(this->m_array, arr.m_array);
        return *this;
  }

  size_t size() const
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