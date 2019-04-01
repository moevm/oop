#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

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
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return !(*this == other);
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &m_node->value;
    }

    list_iterator& operator ++ ()
    {
        if (m_node)
            m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator tmp = *this;
        *this++;
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

    list(const list& other)
    {
        if (!other.empty())
        {
            node<Type>* it_other = other.m_head;
            node<Type>* el;
            m_head = new node<Type>(it_other->value, nullptr, nullptr);
            node<Type>* it_this = m_head;
            for (size_t i = 1; i < other.size(); i++)
            {
                it_other = it_other->next;
                el = new node<Type>(it_other->value, nullptr, it_this);
                it_this->next = el;
                it_this = it_this->next;
            }
            m_tail = it_this;
        }
        else
        {
            m_head = nullptr;
            m_tail = nullptr;
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
        if (this == &other)
            return *this;

        clear();
        if (!other.empty())
        {
            node<Type>* it_other = other.m_head;
            node<Type>* el;
            m_head = new node<Type>(it_other->value, nullptr, nullptr);
            node<Type>* it_this = m_head;
            for (size_t i = 1; i < other.size(); i++)
            {
                it_other = it_other->next;
                el = new node<Type>(it_other->value, nullptr, it_this);
                it_this->next = el;
                it_this = it_this->next;
            }
            m_tail = it_this;
        }
        else
        {
            m_head = nullptr;
            m_tail = nullptr;
        }
        return *this;
    }

    void push_back(const value_type& value)
    {
        node<Type>* tmp = new node<Type>(value, nullptr, m_tail);
        if (empty())
        {
            m_head = tmp;
            m_tail = tmp;
        }
        else
        {
            m_tail->next = tmp;
            m_tail = tmp;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if (pos == m_head)
        {
            push_front(value);
            return begin();
        }
        if (pos == nullptr)
        {
            push_back(value);
            return end();
        }

        node<Type>* el = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev->next = el;
        pos.m_node->prev = el;
        return iterator(el);
    }

    iterator erase(iterator pos)
    {
        if (pos == m_head)
        {
            pop_front();
            return begin();
        }
        if (pos == m_tail)
        {
            pop_back();
            return end();
        }

        pos.m_node->prev->next = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;
        iterator res(pos.m_node->next);
        delete pos.m_node;
        return res;
    }

    void push_front(const value_type& value)
    {
        node<Type>* tmp = new node<Type>(value, m_head, nullptr);
        if (empty())
        {
            m_head = tmp;
            m_tail = tmp;
        }
        else
        {
            m_head->prev = tmp;
            m_head = tmp;
        }
    }

    reference front()
    {
        if (!empty())
            return m_head->value;
    }

    const_reference front() const
    {
        if (!empty())
            return m_head->value;
    }

    reference back()
    {
        if (!empty())
            return m_tail->value;
    }

    const_reference back() const
    {
        if (!empty())
            return m_tail->value;
    }

    void pop_front()
    {
        if (size() == 1)
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
        else if (size())
        {
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
    }

    void pop_back()
    {
        if (size() == 1)
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
        else if (size())
        {
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }

    }

    void clear()
    {
        node<Type>* tmp = m_head;
        while(m_head)
        {
            tmp = m_head;
            m_head = m_head->next;
            delete tmp;
        }
        m_head = nullptr;
        m_tail = nullptr;
    }

    bool empty() const
    {
        return m_head == nullptr;
    }

    size_t size() const
    {
        size_t size = 0;
        node<Type>* tmp = m_head;
        while (tmp)
        {
            tmp = tmp->next;
            size++;
        }
        return size;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

#endif // LIST_H
