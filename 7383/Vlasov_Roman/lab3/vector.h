#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

#include <iostream>

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
        assert(count >= 0);
        if (count)
        {
            m_first = new value_type[count];
            m_last = m_first + count;
        }
        else {
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        assert(last - first >= 0);
        m_first = new value_type[last - first];
        m_last = m_first + (last - first);
        std::copy(first, last, m_first);

    }

    vector(std::initializer_list<Type> init)
    {
        if (init.size() > 0)
        {
            m_first = new value_type[init.size()];
            m_last = m_first + init.size();
            std::copy(init.begin(), init.end(), m_first);
        }
        else {
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(const vector& other)
    {
        if (!other.empty())
        {
            m_first = new value_type[other.size()];
            m_last = m_first + other.size();
            std::copy(other.begin(), other.end(), m_first);

        }
        else {
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(vector&& other)
    {
        m_first = other.begin();
        m_last = other.end();
        other.m_last = nullptr;
        other.m_first = nullptr;
    }

    ~vector()
    {
        if (!empty())
            delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        if (m_first != other.begin())
        {
            if (!empty())
                delete[] m_first;
            if (!other.empty())
            {
                m_first = new value_type[other.size()];
                m_last = m_first + other.size();
                std::copy(other.begin(), other.end(), m_first);
            }
            else {
                m_first = nullptr;
                m_last = nullptr;
            }
        }
        return *this;
    }

    vector& operator=(vector&& other)
    {
        if (m_first != other.begin())
        {
            if (!empty())
                delete[] m_first;
            m_first = other.begin();
            m_last = other.end();
            other.m_last = nullptr;
            other.m_first = nullptr;
        }
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        assert(last - first >= 0);
        if (!empty())
            delete[] m_first;
        m_first = new value_type[last - first];
        m_last = m_first + (last - first);
        std::copy(first, last, m_first);
    }

    // resize methods
    void resize(size_t count)
    {
        assert(count >= 0);
        if (count)
        {
            iterator tmp = new value_type[count];
            if (!empty())
            {
                std::copy(m_first, (size() < count ? m_last : m_first + count), tmp);
                delete[] m_first;
            }
            m_first = tmp;
            m_last = tmp + count;
        }
        else {
            if (!empty())
                delete[] m_first;
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        assert(pos - m_first >= 0);
        assert(m_last - pos >= 0);
        difference_type p = pos - m_first;
        push_back(value);
        std::rotate(m_first + p, m_last - 1, m_last);
        return m_first + p;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        assert(pos - m_first >= 0);
        assert(m_last - pos >= 0);
        assert(last - first >= 0);
        difference_type p = pos - m_first;
        difference_type s = last - first;
        resize(size() + s);
        std::copy(first, last, m_last - s);
        std::rotate(m_first + p, m_last - s, m_last);
        return m_first + p;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        resize(size() + 1);
        *(m_last - 1) = value;
    }


    //erase methods
    iterator erase(const_iterator pos)
    {
        assert(pos - m_first >= 0);
        assert(m_last - pos >= 0);
        difference_type p = pos - m_first;
        std::rotate(m_first + p, m_first + p + 1, m_last);
        resize(size() - 1);
        return m_first + p;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        assert(first - m_first >= 0);
        assert(m_last - last >= 0);
        assert(last - first >= 0);
        difference_type p = first - m_first;
        difference_type s = last - first;
        std::rotate(m_first + p, m_first + p + s, m_last);
        resize(size() - s);
        return m_first + p;
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
#endif // VECTOR_H
