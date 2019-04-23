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

    explicit vector(size_t count = 0):
    m_first(count ? new value_type[count] : nullptr),
    m_last(m_first+count)
    {
        
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):
    m_first(last-first ? new value_type[last-first] : nullptr),
    m_last(m_first+(last-first))
    {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init):
    m_first(init.end()-init.begin() ? new value_type[init.end()-init.begin()] : nullptr),
    m_last(m_first+(init.end()-init.begin()))
    {
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other):
    m_first(other.m_last-other.m_first ? new value_type[other.m_last-other.m_first] : nullptr),
    m_last(m_first+(other.m_last-other.m_first))
    {
        std::copy(other.m_first, other.m_last, m_first);
    }

    vector(vector&& other)
    {
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }


    //assignment operators
    vector& operator=(const vector& other)
    {
    if(other.m_first == m_first)
        return *this;
    size_t count = other.m_last - other.m_first;
    if(count == 0){
        delete[] m_first;
        m_first = nullptr;
        m_last = nullptr;
        return *this;
    }
    delete[] m_first;
    m_first = new value_type[count];
    std::copy(other.m_first, other.m_last, m_first);
    m_last = m_first+count;
    return *this;
    }

    vector& operator=(vector&& other)
    {
        delete[] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete[] m_first;
        size_t count = last-first;
        m_first = count ? new value_type[count] : nullptr;
        m_last = m_first+count;
        std::copy(first, last, m_first);
    }

    void resize(size_t count)
    {
        size_t N = count;
        iterator tmp = count ? new value_type[count] : nullptr;
        if(count > m_last-m_first)
            count = m_last-m_first;
        for(size_t i = 0; i < count; i++)
            tmp[i] = m_first[i];
        delete[] m_first;
        m_first = tmp;
        m_last = m_first+N;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        size_t count = 0;
        iterator tmp = m_first;
        while(tmp!=pos){
            tmp++;
            count++;
        }
        std::rotate(tmp, tmp+1, m_last);
        resize(m_last-m_first-1);
        return m_first+count;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_t count = 0;
        
        iterator tmp = m_first;
        while(tmp!=first){
            tmp++;
            count++;
        }
        for(size_t i = 0; i < last-first; i++){
            tmp = erase(tmp);
        }
        return m_first+count;
    }


    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t N = m_last-m_first;
        iterator tmp = new value_type[N+1];
        size_t count = pos-m_first;
        for(int i = 0; i < count; i++)
            tmp[i] = m_first[i];
        tmp[count] = value;
        for(int i = count; i < N; i++)
            tmp[i+1] = m_first[i];
        
        delete[] m_first;
        m_first = tmp;
        m_last = m_first+N+1;
        return m_first+count;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t N = m_last-m_first;
        iterator tmp = new value_type[m_last-m_first+(last-first)];
        size_t count = pos-m_first;
        for(int i = 0; i < count; i++)
            tmp[i] = m_first[i];
        for(int i = 0; i < last-first; i++)
            tmp[i+count] = first[i];
        for(int i = 0; i < N-count; i++)
            tmp[count+(last-first)+i] = m_first[count+i];
        delete[] m_first;
        m_first = tmp;
        m_last = m_first+N+(last-first);
        return m_first+count;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        size_t count = m_last-m_first;
        iterator tmp = new value_type[count+1];
        std::copy(m_first, m_last, tmp);
        tmp[count] = value;
        delete[] m_first;
        m_first = tmp;
        m_last = m_first+count+1;
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

int main(){

    return 0;
}