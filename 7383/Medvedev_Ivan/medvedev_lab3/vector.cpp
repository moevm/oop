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
      m_first = new Type[count];
      m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        size_t size = last - first;
        m_first = new Type[size];
        if (size){
            std::copy (first, last, m_first);
            m_last = m_first + size;
        }
        else{
            delete[] m_first;
            m_first = NULL;
            m_last = NULL;
        }
    }

    vector(std::initializer_list<Type> init)
    {
        size_t size = init.end() - init.begin();
        m_first = new Type[size];
        if(size){
            std::copy (init.begin(), init.end(), m_first);
            m_last = m_first + size;
        }
        else{
            delete[] m_first;
            m_first = NULL;
            m_last = NULL;
        }
    }

    vector(const vector& other)
    {
        size_t size = other.size();
        m_first = new Type[size];
        if (size){
            std::copy(other.begin(), other.end(), m_first);
            m_last = m_first + size;
        }
        else{
            delete[] m_first;
            m_first = NULL;
            m_last = NULL;
        }
    }

    vector(vector&& other):m_first(other.begin() ? other.begin() : NULL), m_last(other.end() ? other.end() : NULL)
    {
         other.m_first = NULL;
         other.m_last = NULL;
    }
      
    ~vector()
    {
      delete[] m_first;
      m_first = NULL;
      m_last = NULL;
    }
      

    //assignment operators
    vector& operator=(const vector& other)
    {
        if(m_first)
            delete[] m_first;;
        size_t size = other.size();
        if (size){
            m_first = new Type[size];
            std::copy(other.begin(), other.end(), m_first);
            m_last = m_first + size;
        }
        else{
            m_first = m_last = NULL;
        }
        return *this;
    }

    vector& operator=(vector&& other)
    {
      if(m_first){
          delete[] m_first;
          m_first = other.begin();
          m_last = other.end();
          other.m_last = other.m_first = NULL;
      }
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        if(m_first)
            delete[] m_first;
        size_t size = last - first;
        m_first = new Type[size];
        std::copy(first, last, m_first);
        m_last = m_first + size;
    }

    // resize methods
    void resize(size_t count)
    {
         Type* tmp = new Type[count];
         size_t new_size = count;
         if (count < size()){
             for (unsigned i = 0; i < new_size; i++)
                 tmp[i] = m_first[i];
         }
         else{
             for (unsigned i = 0; i < size(); i++)
                 tmp[i] = m_first[i];
         }
         delete[] m_first;
         m_first = tmp;
         m_last = tmp + count;
           
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t dif = pos - m_first;
      Type* tmp = const_cast<Type*> (pos);
      std::rotate(tmp, tmp + 1, m_last);
      resize(size()-1);
      return dif + m_first;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t dif = first - m_first;
      size_t length = last - first;
      std::rotate(m_first + dif, m_first + length + dif, m_last);
      resize(m_last - m_first - length);
      return dif + m_first;
      
    }

    
    
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t dif = pos - m_first;
      resize(size() + 1);
      *(m_last - 1) = value;
      std::rotate(m_first + dif, m_last-1, m_last);
      return m_first + dif;
      
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t size_ = size();
      size_t length = last - first;
      Type* tmp = new Type [size() + length];
      size_t dif = pos - m_first;
      std::copy(m_first, m_last, tmp);
      std:: copy(first, last, tmp + size());
      std::rotate(tmp + dif, tmp + size(), tmp + size() + length);
      delete[] m_first;
      m_first = tmp;
      m_last = tmp + size_ + length;
      return m_first + dif;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(end(), value);
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
