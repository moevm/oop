#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0) : m_first(count ? new value_type[count] : nullptr) ,m_last(m_first + count)
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last - first)
    {
      std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.size())
    {
      std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other) : vector(other.size())  //конструктор копирования
    {
      std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other)  //конструктор перемещения
    {
      m_first = other.begin();
      m_last = other.end();
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      delete[] m_first;
      m_first = nullptr;
      m_last = nullptr;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      if(this!=&other)
      {
        vector tmp(other);
        std::swap((*this).m_first, tmp.m_first);
        std::swap((*this).m_last, tmp.m_last);
      }
      return *this;
    }

    vector& operator=(vector&& other)
    {
      if(this!=&other)
      {
        std::swap((*this).m_first, other.m_first);
        std::swap((*this).m_last, other.m_last);
      }
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector tmp(first, last);
      std::swap((*this).m_first, tmp.m_first);
      std::swap((*this).m_last, tmp.m_last);
    }

    void resize(size_t count)
    {
      if(count!=size())
      {
        iterator temp = new value_type[count];
        if(count < size())
          std::copy (m_first, (m_first + count), temp);
        else
          std::copy (m_first, m_last, temp);
        delete[] m_first;
        m_first = temp;
        m_last = m_first + count;
      }
    }
    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t lenght = size() - 1;
      size_t index = pos - m_first;
      iterator temp = new value_type[lenght];
      std::copy(m_first, (iterator)pos, temp);
      std::copy((iterator)pos+1, m_last, temp + index);
      delete[] m_first;
      m_first = temp;
      m_last = m_first + lenght;
      return m_first + index;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t lenght = size() - (last - first);
      size_t index = first - m_first;
      iterator temp = new value_type[lenght];
      std::copy(m_first, (iterator)first, temp);
      std::copy((iterator)last, m_last, temp + index);
      delete[] m_first;
      m_first = temp;
      m_last = m_first + lenght;
      return m_first + index;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t index = pos - m_first;
      size_t new_size = size() + 1;
      resize(new_size);
      std::copy(m_first + index, m_last, m_first + index + 1);
      m_first[index] = value;
      return m_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
     size_t size = m_last - m_first;
     size_t size_add = last - first;
     size_t index = pos - m_first;
     Type new_arr[size];
     std::copy(m_first, m_last, new_arr);
     resize(size + size_add);
     std::copy(new_arr, new_arr + index, m_first); //записываем первую часть до pos
     std::copy(first, last, m_first + index); //вставка
     std::copy(new_arr + index, new_arr + size, m_first + index + size_add); //записываем оставшуюся часть
     return m_first + index;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(m_last, value);
    }

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
