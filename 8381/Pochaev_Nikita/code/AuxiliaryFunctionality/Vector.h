#ifndef OOP_VECTOR_H
#define OOP_VECTOR_H

#include <cstdint>      // primitive type typedefs
#include <memory>       // std::unique_ptr
#include <algorithm>    // std::move_backward

/**
 * cds - custom data structures
 */
namespace cds {
    template<typename T>
    class Vector {
    private:
        // as boost::scoped_array
        // pointer on array
        std::unique_ptr<T[]> m_buffer;
        std::size_t m_vec_size;
        std::size_t m_vec_capacity;

        using iterator = T*;
        using reverse_iterator = T*;

        using reference = T&;

        //~Vector() = default;
    private:
        // inline function, avoids having to make direct std::make_unique calls
        inline void realloc_vector(const std::size_t n) noexcept
        {
            m_buffer = std::make_unique<T[]>(n);
        }

        inline void swap(Vector<T> &vec) noexcept
        {
            std::swap(m_vec_size, vec.m_vec_size), std::swap(m_vec_capacity, vec.m_vec_capacity);
        }

        inline std::size_t get_position(const iterator it) const noexcept { return it - m_buffer.get(); }

    public:
        explicit Vector(const std::size_t vec_capacity) noexcept :
                m_vec_capacity(vec_capacity),
                m_vec_size(0)
        {
            m_buffer = std::make_unique<T[]>(vec_capacity);
        }

        // size and capacity set to 0 by default constructor
        explicit constexpr Vector() noexcept :
                m_vec_size(0),
                m_vec_capacity(0),
                m_buffer(nullptr) {};

        Vector(const std::initializer_list<T> &init) noexcept(false) :
                m_vec_capacity(init.size()),
                m_vec_size(init.size()) {
            m_buffer = std::make_unique<T[]>(init.size());

            std::copy(init.begin(), init.end(), m_buffer.get());
        }

        // copy constructor, copes x elements into another Vector
        Vector(const Vector<T> &vec) noexcept :
                m_vec_size(vec.m_vec_size),         // copy Vector size
                m_vec_capacity(vec.m_vec_capacity)  // copy Vector capacity
        {
            // allocate new unique_ptr buffer
            realloc_vector(m_vec_capacity);

            // copy elements into new Vector
            std::copy(vec.m_buffer.get(), vec.m_buffer.get() + vec.size(), this->m_buffer.get());

            /*
            for(size_t i = 0; i < vec.size(); i++)
            {
                this->m_buffer[i] = vec[i];
            }
             */
        }

        // move constructor, moves the members and then switches places with the old Vector
        Vector(Vector<T> &&vec) noexcept :
                m_vec_capacity(0),
                m_vec_size(0) {
            // move basic members.
            m_vec_size = std::move(vec.m_vec_size);
            m_vec_capacity = std::move(vec.m_vec_capacity);

            // move buffer.
            m_buffer = std::move(vec.m_buffer);
        }

        // copy assignment operator, copes x elements into another Vector
        Vector &operator=(const Vector<T> &vec) noexcept
        {
            // swap two members (size, capacity).
            this->swap(*this);

            // allocate new unique_ptr buffer.
            realloc_vector(m_vec_capacity);

            std::copy(vec.m_buffer.get(), vec.m_buffer.get() + vec.size(), this->m_buffer.get());

            return *this;
        }

        // move assignment operator, moves the members and then switches places with the old Vector
        Vector &operator=(Vector<T> &&vec) noexcept
        {
            if (this == vec)
                return *this;

            // move basic members
            m_vec_size = std::move(vec.m_vec_size);
            m_vec_capacity = std::move(vec.m_vec_capacity);

            // move buffer
            m_buffer = std::move(vec.m_buffer);

            return *this;
        }

    public:
        inline T &operator[](const std::size_t element_index) const noexcept { return this->m_buffer[element_index]; }

        // capacity functions

        // Returns x amount of elements existing in the dynamic-array
        [[nodiscard]] constexpr std::size_t size() const noexcept { return m_vec_size; }

        // returns Vector capacity
        [[nodiscard]] constexpr std::size_t capacity() const noexcept { return m_vec_capacity; }

        [[nodiscard]] constexpr bool empty() const noexcept { return m_vec_size == 0; }

        constexpr iterator begin() const noexcept { return m_buffer.get(); }

        constexpr iterator end() const noexcept { return m_buffer.get() + this->size(); }

        constexpr reverse_iterator rbegin() const noexcept { return m_buffer.get() + this->size(); }

        constexpr reverse_iterator rend() const noexcept { return m_buffer.get(); }

        // iterator erase() noexcept {}

        // reallocates Vector to change it's capacity
        void resize(const std::size_t n) noexcept(false)
        {
            reserve(n);
        }

        void push_back(const T &val) noexcept(false)
        {
            // reserve Vector if we exceed capacity (this will reallocate the buffer)
            if (this->size() >= this->capacity())
                reserve(this->capacity() + 1);

            m_buffer[m_vec_size++] = T(val);
        }

        void push_back(T &&val) noexcept(false) {
            if (this->size() >= this->capacity())
                reserve(this->capacity() + 1);

            // not perfect forwarded due to the existing overload which takes an lvalue reference
            m_buffer[m_vec_size++] = T(std::move(val));
        }

        // destroys the last element and decrements the size
        void pop_back() noexcept {
            if (this->empty())
                return;

            if constexpr(!std::is_trivially_destructible<T>::value)
                m_buffer[m_vec_size--].~T();
        }

        // Inserts a new element before pos, args are forwarded to T
        template<typename... Args>
        iterator emplace(const iterator pos, Args &&... args) noexcept(false)
        {
            if (this->size() >= this->capacity())
                reserve(this->capacity() + 1);

            std::move_backward(pos, this->end(), this->end() + 1);

            // forward arguments to T.
            m_buffer[this->get_position(pos)] = T(std::forward<Args>(args)...);

            m_vec_size++;

            return pos;
        }

        // inserts a new element at the end of buffer, args are forwarded to T
        template<typename... Args>
        void emplace_back(Args &&... args) noexcept(false)
        {
            if (this->size() >= this->capacity())
                reserve(this->capacity() + 1);

            m_buffer[m_vec_size++] = T(std::forward<Args>(args)...);
        }

        template<typename... Args>
        T &emplace_back(Args &&... args) noexcept(false)
        {
            if (this->capacity() >= this->size())
                reserve(this->capacity() + 1);

            return m_buffer[m_vec_size++] = T(std::forward<Args>(args)...);
        }

        // reallocates Vector to match the capacity to element size
        void shrink_to_fit() noexcept(false)
        {
            if (!this->empty() && this->capacity() >= this->size())
                reserve(this->size());
        }

        reference at(const std::size_t n) const noexcept(false)
        {
            if (n > this->size())
                throw std::out_of_range("Vector element position is out of bounds");

            return m_buffer[n];
        }

        reference front() const noexcept { return m_buffer[0]; }

        reference back() const noexcept { return m_buffer[this->size() - 1]; }

        // inserts x at either the start or end of the buffer
        void insert(const iterator pos, const T &val) noexcept
        {
            if (this->size() >= this->capacity())
                reserve(this->capacity() + 1);

            const iterator it = &m_buffer[this->get_position(pos)];

            std::move_backward(pos, this->end(), this->end() + 1);

            (*it) = T(val);

            m_vec_size++;
        }

        void insert(const iterator pos, T &&val) noexcept(false)
        {
            if (this->size() >= this->capacity())
                reserve(this->capacity() + 1);

            const iterator it = &m_buffer[this->get_position(pos)];

            std::move_backward(pos, this->end(), this->end() + 1);

            (*it) = T(std::move(val));

            m_vec_size++;
        }

        void assign(const std::size_t n, T &val) noexcept
        {
            if (this->size() >= this->capacity())
                reserve(this->capacity() + n);

            std::fill_n(this->begin(), n, T(val));

            m_vec_size = n;
        }

        void assign(const std::initializer_list<T> &il) noexcept(false)
        {
            realloc_vector(il.size());

            std::copy(il.begin(), il.end(), this->m_buffer.get());

            m_vec_size = il.size();

            m_vec_capacity = il.size();
        }

        void assign(const iterator first, const iterator last) noexcept(false)
        {
            std::copy(first, last, this->m_buffer.get());
        }

        void reserve(const std::size_t n) noexcept(false)
        {
            // this will hold the current buffer data
            std::unique_ptr<T[]> temporary_buffer = std::make_unique<T[]>(n);

            // copy current buffer data into the new buffer
            std::copy(this->m_buffer.get(), this->m_buffer.get() + this->size(), temporary_buffer.get());

            realloc_vector(n);

            this->m_vec_capacity = n;

            // Vector has been reallocated, so we transfer ownership of the temporary buffer to the main one
            m_buffer = std::move(temporary_buffer);
        }

        iterator erase(const iterator position) noexcept
        {
            if (this->empty())
                return position;

            // hold pointer to buffer position via iterator
            const iterator it = &m_buffer[this->get_position(position)];

            (*it).~T();

            std::copy(position + 1, this->end(), position);

            m_vec_size--;

            return it;
        }

        iterator erase(const iterator first, const iterator last) noexcept
        {
            const iterator it = &m_buffer[this->get_position(first)];

            std::for_each(first, last, [](reference ref) { ref.~T(); });

            m_vec_size = 0;

            return it;
        }

        void clear() noexcept(false) {
            if (this->empty())
                return;

            std::for_each(this->begin(), this->end(), [](reference ref) { ref.~T(); });

            m_vec_size = 0;
        }

        constexpr T *data() const noexcept { return this->m_buffer.get(); }
    };

    // OPERATOR OVERLOADS

    template<typename T>
    bool operator== (const Vector<T> &lhs, const Vector<T> &rhs) noexcept(false)
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename T>
    bool operator!= (const Vector<T> &lhs, const Vector<T> &rhs) noexcept(false)
    {
        return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename T>
    bool operator< (const Vector<T> &lhs, const Vector<T> &rhs) noexcept(false)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<typename T>
    bool operator<= ([[maybe_unused]] const Vector<T> &lhs, [[maybe_unused]] const Vector<T> &rhs) noexcept(false)
    {
        return false;
    }

    template<typename T>
    bool operator> ([[maybe_unused]] const Vector<T> &lhs, [[maybe_unused]] const Vector<T> &rhs) noexcept(false)
    {
        return false;
    }

    template<typename T>
    bool operator>= ([[maybe_unused]] const Vector<T> &lhs, [[maybe_unused]] const Vector<T> &rhs) noexcept(false)
    {
        return false;
    }
}

#endif //OOP_VECTOR_H
