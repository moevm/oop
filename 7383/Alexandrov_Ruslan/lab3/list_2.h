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
    class list; //forward declaration

    template<class Type>
    class list_iterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef Type value_type;
        typedef Type *pointer;
        typedef Type &reference;
        typedef size_t size_type;
        typedef std::forward_iterator_tag iterator_category;

        list_iterator()
                : m_node(NULL) {
        }

        list_iterator(const list_iterator &other)
                : m_node(other.m_node) {
        }

        list_iterator &operator=(const list_iterator &other) {
            m_node = other.m_node;
            return *this;
            // implement this
        }

        bool operator==(const list_iterator &other) const {
            return m_node == other.m_node;
            // implement this
        }

        bool operator!=(const list_iterator &other) const {
            return m_node != other.m_node;
            // implement this
        }

        reference operator*() {
            return m_node->value;
            // implement this
        }

        pointer operator->() {
            return &(m_node->value);
            // implement this
        }

        list_iterator &operator++() {
            m_node = m_node->next;
            return *this;
        }

        list_iterator operator++(int) {
            auto ret = *this;
            m_node = m_node->next;

            return ret;
        }

    private:
        friend class list<Type>;

        list_iterator(node<Type> *p)
                : m_node(p) {
        }

        node<Type> *m_node;
    };

    template<class Type>
    class list {
    public:
        typedef Type value_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef list_iterator<Type> iterator;

        list()
                : m_head(nullptr), m_tail(nullptr) {
        }

        ~list() {
            clear();
            // implement this
        }

        list::iterator begin() {
            return iterator(m_head);
        }

        list::iterator tail() {
            return iterator(m_tail);
        }

        list::iterator currentNode(node<Type> *current) {
            return iterator(current);
        }

        list::iterator end() {
            return iterator();
        }

        list(const list &other) : m_head(nullptr), m_tail(nullptr) {
            node<Type> *current = m_head;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
            delete current;
        }

        list(list &&other) {
            m_head = other.m_head;
            m_tail = other.m_tail;
            delete other.m_tail;
            delete other.m_head;
            other.m_head = nullptr;
            other.m_tail = nullptr;
        }

        list &operator=(const list &other) {
            if (this != &other) {
                clear();
                node<Type> *current = m_head;
                while (current != nullptr) {
                    push_back(current->value);
                    current = current->next;
                }
                delete current;
            }
            return *this;
        }

        void push_back(const value_type &value) {
            if (empty()) {
                m_tail = new node<Type>(value, nullptr, nullptr);
                m_head = m_tail;
                return;
            } else {
                m_tail->next = new node<Type>(value, nullptr, m_tail);
                m_tail = m_tail->next;
            }
        }

        iterator insert(iterator pos, const Type &value) {
            if (pos.m_node == nullptr) {
                push_back(value);
                return tail();
            } else if (pos.m_node == m_head) {
                push_front(value);
                return begin();
            } else {
                pos.m_node->prev->next = new node<Type>(value, pos.m_node, pos.m_node->prev);
                pos.m_node->prev = pos.m_node->prev->next;
                return currentNode(pos.m_node->prev);
            }
            // implement this
        }

        iterator erase(iterator pos) {
            if (pos.m_node == nullptr) {
                return nullptr;
            }
            if (pos.m_node == m_head) {
                pop_front();
                return iterator(m_head);
            } else if (pos.m_node == m_tail) {
                pop_back();
                return iterator(m_tail);
            } else {
                node<Type> *current = pos.m_node->next;
                current->prev = pos.m_node->prev;
                current->prev->next = current;
                delete pos.m_node;
                return currentNode(current);
            }
            // implement this
        }

        void push_front(const value_type &value) {
            if (empty()) {
                m_head = new node<Type>(value, nullptr, nullptr);
                m_tail = m_head;
                return;
            } else {
                m_head->prev = new node<Type>(value, m_head, nullptr);
                m_head = m_head->prev;
            }
        }

        reference front() {
            return m_head->value;
            // implement this
        }

        const_reference front() const {
            return m_head->value;
            // implement this
        }

        reference back() {
            return m_tail->value;
            // implement this
        }

        const_reference back() const {
            return m_tail->value;
            // implement this
        }

        void pop_front() {
            if (m_head == nullptr) return;
            if (m_head == m_tail) {
                delete m_head;
                m_tail = m_head = nullptr;
            } else {
                m_head = m_head->next;
                delete m_head->prev;
                m_head->prev = nullptr;
            }
        }

        void pop_back() {
            if (m_tail == nullptr) return;
            if (m_tail == m_head) {
                delete m_tail;
                m_tail = m_head = nullptr;
            } else {
                m_tail = m_tail->prev;
                delete m_tail->next;
                m_tail->next = nullptr;
            }
        }

        void clear() {
            while (!empty()) {
                pop_back();
            }
            // implement this
        }

        bool empty() const {
            return m_head == nullptr;
            // implement this
        }

        size_t size() const {
            int length = 0;
            node<Type> *current = m_head;
            while (current != nullptr) {
                current = current->next;
                length++;
            }
            return length;
        }

    private:
        //your private functions

        node<Type> *m_head;
        node<Type> *m_tail;
    };

}// namespace stepik