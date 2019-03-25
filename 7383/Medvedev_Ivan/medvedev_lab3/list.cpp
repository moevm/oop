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
    }

    bool operator == (const list_iterator& other) const
    {
      return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
      return m_node != other.m_node;
    }

    reference operator * ()
    {
      return m_node->value;
    }

    pointer operator -> ()
    {
      return &m_node->value;
    }

    list_iterator& operator ++ () //prefix
    {
      m_node = m_node->next;
      return *this;
    }

    list_iterator operator ++ (int) //postfix
    {
        list_iterator tmp(m_node);
        m_node = m_node->next;
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

    void push_back(const value_type& value)
    {
      if (!m_head){
          m_head = new node<Type> (value, nullptr, nullptr);
          m_tail = m_head;
      }
      else{
          m_tail->next = new node<Type>(value, nullptr, m_tail);
          m_tail->next->prev = m_tail;
          m_tail = m_tail -> next;
      }
    }

    void push_front(const value_type& value)
    {
        if (!m_head)
            m_tail = m_head = new node<Type> (value, nullptr, nullptr);
        else{
            m_head->prev = new node <Type> (value, m_head, nullptr);
            m_head->prev->next = m_head;
            m_head = m_head->prev;
        }
    }

    reference front()
    {
      return m_head->value;
    }

    const_reference front() const
    {
      return m_head->value;
    }

    reference back()
    {
      return m_tail->value;
    }

    const_reference back() const
    {
      return m_tail->value;
    }

    void pop_front()
    {
      if(m_head->next){
          m_head = m_head->next;
          delete m_head->prev;
          m_head->prev = nullptr;
      }
      else{
          m_head->next = nullptr;
          delete m_head;
          m_head = m_tail =nullptr;
      }
    }

    void pop_back()
    {
      if(m_tail->prev){
          m_tail = m_tail->prev;
          delete m_tail->next;
          m_tail->next = nullptr;
      }
      else{
          m_tail->prev = nullptr;
          delete m_tail;
          m_tail = m_head = nullptr;
      }
          
    }

    void clear()
    {
        while(m_head != m_tail){
            m_head = m_head->next;
            delete m_head->prev;
        }
        delete m_head;
        m_head = m_tail = nullptr;
    }

    bool empty() const
    {
      return m_head == nullptr;
    }

    size_t size() const
    {
        if(empty()){
            return 0;
         }
        size_t size = 0;
        auto tmp = m_head;
        while(tmp){
            size++;
            tmp = tmp->next;
          }
        return size; 
    }
      
    ~list()
    {
      clear();    
    }

    list(const list& other)
    {
      if (other.m_head == nullptr){
          m_head = nullptr;
          m_tail = nullptr;
          return;
      }

      auto tmp = other.m_head;
      m_head = new node<Type> (tmp->value, nullptr, nullptr);
      tmp = tmp->next;
      m_tail = new node<Type> (tmp->value, nullptr, m_head);
      m_head->next = m_tail;
      tmp = tmp->next;
      while (tmp){
          m_tail->next = new node<Type> (tmp->value, nullptr, m_tail);
          m_tail = m_tail -> next;
          tmp = tmp->next;
      }
          
          
    }

    list(list&& other)
    {
      m_head = other.m_head;
      m_tail = other.m_tail;
      other.m_head = nullptr;
      other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
      if (m_head == other.m_head)
          return *this;
      if (m_head)
          clear();
      auto tmp = other.m_head;
      m_head = new node<Type> (tmp->value, nullptr, nullptr);
      tmp = tmp->next;
      m_tail = new node<Type> (tmp->value, nullptr, m_head);
      m_head->next = m_tail;
      tmp = tmp->next;
      while (tmp){
          m_tail->next = new node<Type> (tmp->value, nullptr, m_tail);
          m_tail = m_tail -> next;
          tmp = tmp->next;
        }
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }


    iterator insert(iterator pos, const Type& value)
    {
      if(pos.m_node == nullptr){
          push_back(value);
          return iterator(m_tail);
      }
      if (pos.m_node->prev == nullptr){
          push_front(value);
          return iterator(m_head);
      }
      node<Type>* tmp = new node <Type>(value, pos.m_node, pos.m_node->prev);
      tmp->prev->next = tmp;
      tmp->next->prev = tmp;
      return iterator(tmp);
          
    }

    iterator erase(iterator pos)
    {
      if (pos.m_node == nullptr)
          return end();
      if(pos.m_node->next == nullptr){
          pop_back();
          return end();
      }
      if (pos.m_node->prev == nullptr){
          pop_front();
          return begin();
      }
      node<Type>* tmp = pos.m_node->next;
      pos.m_node->prev->next = pos.m_node->next;
      pos.m_node->next->prev = pos.m_node->prev;
      delete pos.m_node;
      return iterator(tmp);
    }



  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
