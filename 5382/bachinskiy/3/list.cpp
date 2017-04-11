//
// Created by Максим Бачинский on 11.04.17.
//
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace stepik {
    template<class Type>
    struct node {
        Type value;
        node *next;
        node *prev;

        node(const Type &value, node<Type> *next, node<Type> *prev)
                : value(value), next(next), prev(prev) {
        }
    };

    template<class Type>
    class list {
    public:
        typedef Type value_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;

        list()
                : m_head(nullptr), m_tail(nullptr) {
        }

        void push_back(const value_type &value) {
            node<value_type> *n = new node<value_type>(value, nullptr, this->m_tail);
            m_tail = n;
        }

        void push_front(const value_type &value) {
            node<value_type> *n = new node<value_type>(value, this->m_head, nullptr);
            m_head = n;
        }

        reference front() {
            return m_head->value;
        }

        const_reference front() const {
            return m_head;
        }

        reference back() {
            return m_tail->value;
        }

        const_reference back() const {
            return m_tail;
        }

        void pop_front() {
            node<value_type>* newHead = m_head->next;
            newHead->prev = nullptr;
            delete m_head;
            m_head = newHead;
        }

        void pop_back() {
            node<value_type>* newTail = m_tail->prev;
            newTail->next = nullptr;
            delete m_tail;
            m_tail = newTail;
        }

        void clear() {
            while (m_head != m_tail) {
                node<value_type>* newHead = m_head->next;
                delete m_head;
                m_head = newHead;
            }
            delete m_tail;
        }

        bool empty() const {
            return m_head == 0;
        }

        size_t size() const {
            size_t s = 1;
            node<value_type>* n = m_head;
            while (n != m_tail) {
                s++;
                n = n->next;
            }
            return s;
        }

    private:
        //your private functions

        node<Type> *m_head;
        node<Type> *m_tail;
    };

}// namespace stepik
