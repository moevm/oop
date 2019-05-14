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
            // implement this
            m_first = new Type[count];
            m_last = m_first + count;
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            // implement this
            m_first = new Type[last-first];
            m_last = m_first + (last-first);
            std::copy(first, last, m_first);

        }

        vector(std::initializer_list<Type> init) : vector(init.begin(),init.end())
        {
            // implement this

        }

        vector(const vector& other) :  vector(other.begin(), other.end())
        {
//            std::copy(other.m_first, other.m_last, this->m_first);
            // implement this
        }

        vector(vector&& other)
        {
            vector(other.begin(), other.end());
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_last = nullptr;
            other.m_first = nullptr;
            // implement this
        }

        ~vector()
        {
            delete[] m_first;
            // implement this
        }

        vector &operator=(const vector &array) {
            if (this != &array) {
                delete [] m_first;
                m_first = new Type[array.size()];
                m_last = m_first + array.size();
                std::copy(array.begin(), array.end(), m_first);
            }
            return *this;
        }

        vector& operator=(vector&& array)
        {
            if (this != &array) {
                delete[] m_first;
                m_first = array.m_first;
                m_last = m_first + array.size();
                array.m_first = nullptr;
                array.m_last = nullptr;
            }
            return *this;
        }

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            delete[] m_first;
            m_first = new Type[last - first];
            m_last = m_first + last - first;
            std::copy(first, last, m_first);
        }

        void resize(size_t count)
        {
            if (count == this->size()) {
                return;
            }
            iterator tempArray = new Type[count];
            if (count > this->size()) {
                std::copy(m_first, m_first + this->size(), tempArray);
            } else {
                std::copy(m_first, m_first + count, tempArray);
            }
            delete[] m_first;
            m_first = tempArray;
            m_last = m_first + count;
        }

        iterator erase(const_iterator pos)
        {
            size_t temp = pos - m_first;
            size_t newSize = this->size() - 1;
            std::rotate(temp + m_first, m_first + temp + 1, m_last);
            resize(newSize);
            return m_first + temp;
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            size_t firstIt = first - m_first;
            size_t secondIt = last - m_first;
            size_t distance = secondIt - firstIt;
            size_t newSize = this->size() - distance;
            std::rotate(firstIt + m_first, m_first + secondIt, m_last);
            resize(newSize);
            return m_first + firstIt;
        }

        iterator insert(const_iterator pos, const Type& value)
        {
            size_t offset = pos - m_first;
            push_back(value);
            std::rotate(m_first+offset, m_last-1, m_last);

            return m_first + offset;
        }

        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            size_t temp = pos - m_first;
            size_t distance = last - first;
            resize(this->size() + distance);
            std::copy(first, last, m_last - distance);
            std::rotate(m_first + temp, m_last - distance, m_last);

            return m_first + temp;
        }

        void push_back(const value_type& value)
        {
            resize(this->size() + 1);
            *(m_last-1) = value;
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