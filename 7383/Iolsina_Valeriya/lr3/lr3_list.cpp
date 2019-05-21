#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list; //forward declaration

  template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
      m_node = other.m_node;
      return *this;
    }

    bool operator == (const list_iterator& other) const
    {
      return (m_node == other.m_node);
    }

    bool operator != (const list_iterator& other) const
    {
      return m_node != other.m_node;
    }

    reference operator * ()
    {
      return m_node -> value;
    }

    pointer operator -> ()
    {
      return &(m_node -> value);
    }

    list_iterator& operator ++ ()
    {
      m_node = m_node -> next;
      return *this;
    }

    list_iterator operator ++ (int)
    {
      list_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    node<Type>* m_node;
};

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
      clear();
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    list(const list& other) : list()
    {
      node <Type> *tmp = other.m_head;
      while(tmp)
      {
          push_back(tmp -> value);
          tmp = tmp -> next;
      }
    }

    list(list&& other) : m_head(other.m_head), m_tail(other.m_tail)
    {
      other.m_head = other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
      if(this!=&other)
      {
        list tmp(other);
        tmp.swap(*this);
      }
      return *this;
    }

    void push_back(const value_type& value)
    {
      node <Type> *tmp = new node <Type> (value, nullptr, m_tail);
      if(empty())
      {
        m_head = tmp;
        m_tail = m_head;
      }
      else
      {
        m_tail -> next = tmp;
        m_tail = tmp;
      }
    }
    void push_front(const value_type& value)
    {
      node <Type> *tmp = new node <Type> (value, m_head, nullptr);
      if(empty())
      {
        m_head = tmp;
        m_tail = m_head;
      }
      else
      {
        m_head -> prev = tmp;
        m_head = tmp;
      }
    }

    reference front()
    {
      return (m_head -> value);
    }

    const_reference front() const
    {
      return (m_head -> value);
    }

    reference back()
    {
      return (m_tail -> value);
    }

    const_reference back() const
    {
      return (m_tail -> value);
    }

    void pop_front()
    {
      node <Type> *tmp = m_head;
      if(size()==1)
        m_head = m_tail = nullptr;
      else
      {
        m_head -> next -> prev = nullptr;
        m_head = m_head -> next;
      }
      delete tmp;
    }
    void pop_back()
    {
      node <Type> *tmp = m_tail;
      if(size()==1)
        m_head = m_tail = nullptr;
      else
      {
        m_tail -> prev -> next = nullptr;
        m_tail = m_tail -> prev;
      }
      delete tmp;
    }

    size_t size() const
    {
      size_t size = 0;
      node <Type> *tmp = m_head;
      while (tmp)
      {
        size++;
        tmp = tmp -> next;
      }
      return size;
    }

    iterator insert(iterator pos, const Type& value)
    {
      if(!pos.m_node)
      {
        push_back(value);
        return iterator(m_tail);
      }
      else if(!pos.m_node->prev)
      {
        push_front(value);
        return iterator(m_head);
      }
      else
      {
        node<Type>* tmp = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev =pos.m_node->prev->next= tmp;
        return iterator(tmp);
      }
    }

    iterator erase(iterator pos)
    {
      if (!pos.m_node)
        return nullptr;
      else if (!pos.m_node->prev)
      {
        pop_front();
        return iterator(m_head);
      }
      else if (!pos.m_node->next)
      {
        pop_back();
        return iterator(m_tail);
      }
      else
      {
        node<Type>* tmp = pos.m_node;
        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;
        iterator n(pos.m_node->next);
        delete tmp;
        return n;
      }
    }

    void clear()
    {
      while(m_head)
          pop_back();
      m_head = m_tail = nullptr;
    }
    bool empty() const
    {
      return (m_head == nullptr);
    }

  private:
    //your private functions
    void swap(list &other)
    {
      std::swap(m_head, other.m_head);
      std::swap(m_tail, other.m_tail);
    }
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
