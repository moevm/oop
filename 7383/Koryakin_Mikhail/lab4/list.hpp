#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
using namespace std;
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
      if(m_node != other.m_node)
            m_node->value = other.m_node->value;
      return *this;
    }

    bool operator == (const list_iterator& other) const
    {
      if(m_node == other.m_node)
            return true;
        else
            return false;
    }

    bool operator != (const list_iterator& other) const
    {
        if(m_node != other.m_node)
            return true;
        else
            return false;
    }

    reference operator * ()
    {
      return m_node->value;
    }

    pointer operator -> ()
    {
      return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        if(m_node->next)
            m_node = m_node -> next;
        else
            m_node = nullptr;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator vrem = *this;
        ++(*this);
        return vrem;
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

        while(m_head){
            delete m_head->prev;
            m_head=m_head->next;

        }
        delete m_tail;
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void push_back(const value_type& value)
    {
      node<value_type>* el = new node<value_type>(value, nullptr, m_tail);
        if(empty()){
            m_head = m_tail = el;
            return;
        }
        else{
            m_tail->next = el;
            m_tail = el;
        }
    }

    void push_front(const value_type& value)
    {
      node<value_type>* el = new node<value_type>(value, m_head, nullptr);
        if(empty()){
            m_head = m_tail = el;
            return;
        }
        m_head->prev = el;
        m_head = el;
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(pos.m_node == nullptr){
            push_back(value);
            return iterator(m_tail);
        }
        if(pos.m_node == m_head){
            push_front(value);
            return iterator(m_head);
        }

            node<Type>* el = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev->next = el;
            pos.m_node->prev = el;

        return iterator(el);
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == m_head){
            pop_front();
            return iterator(m_head);
        }
        if(pos.m_node == m_tail){
            pop_back();
            return iterator(m_tail);
        }
        pos.m_node->prev->next = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;
        iterator res(pos.m_node->next);
        delete pos.m_node;
        return res;
    }

     reference front()
    {
      if(!empty())
            return m_head->value;
    }

    const_reference front() const
    {
      if(!empty())
            return m_head->value;
    }

    reference back()
    {
      if(!empty())
            return m_tail->value;
    }

    const_reference back() const
    {
      if(!empty())
            return m_tail->value;
    }

    void pop_front()
    {
        if(empty())
            return;
        if(m_head->next != nullptr){
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
        else{
            delete m_head;
            m_head = m_tail = nullptr;
        }
    }

    void pop_back()
    {
        if(empty())
            return;

        if(m_tail->prev != nullptr){
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }
        else{
            delete m_tail;
            m_head = m_tail = nullptr;
        }
    }

    void clear()
    {
      node<value_type>* vrem = m_head;
        for(int i=0; i<size(); i++){
            m_head = vrem->next;
            delete vrem;
            vrem = m_head;
        }
    }

    bool empty() const
    {
      if(m_head == nullptr)
          return true;
      else
          return false;
    }

    size_t size() const
    {
        size_t count = 0;
        node<value_type>* vrem = m_head;
        while(vrem){
            vrem = vrem->next;
            count++;
        }
        return count;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
