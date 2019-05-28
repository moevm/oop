#ifndef VECTOR_H
#define VECTOR_H

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

    explicit vector(size_t count = 0)
    {
        count ? m_first = new Type[count] : m_first = nullptr;
        count ? m_last = m_first + count : m_last = nullptr;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last-first)
    {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.size())
    {
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other) : vector(other.size())
    {
        std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other) : vector(other.size())
    {
        std::copy(other.begin(), other.end(), m_first);
        other.clear();
    }

    ~vector()
    {
        this->clear();
    }

    // resize methods
    void resize(size_t count)
    {
        if(count == this->size())
            return;
        if(count == 0)
        {
            this->clear();
            return;
        }
        if(count > this->size())
        {
            iterator tmp = new Type[count];
            for(size_t i=0; i<size(); i++)
            {
                tmp[i] = *(m_first+i);
            }
            clear();
            m_first = tmp;
            m_last = tmp + count;
        }
        else
        {
            iterator tmp = new Type[count];
            for(size_t i = 0; i < count; i++)
            {
                 tmp[i] = m_first[i];
            }
            clear();
            m_first = tmp;
            m_last = m_first + count;
        }
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t i = 0;
        while(m_first + i != pos) i++;
        resize(size() + 1);
        *(m_last - 1) = value;
        std::rotate(m_first+ i, m_last-1, m_last);
        return m_first + i;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t i = 0, digit = last - first;
        while(m_first + i != pos) i++;
        resize(size() + digit);
        for(size_t tmp = 0; tmp < digit; tmp++)
            *(m_last - digit + tmp) = *(first + tmp);
        for(size_t tmp = 0; tmp < digit; tmp++)
            std::rotate(m_first + i, m_last -1, m_last);
        return m_first + i;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        insert(m_last, (Type)value);
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
    void clear()
    {
         if(m_first)
         {
              delete [] m_first;
              m_first = nullptr;
              m_last = nullptr;
          }
     }

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik

#endif // VECTOR_H
