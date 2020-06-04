#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <iostream>

template<typename T>
class Array {
private:
    size_t m_size;
    std::unique_ptr<T[]> m_array;

public:
    explicit Array (const size_t size = 0) {
        m_size = size;
        if (m_size > 0) m_array = std::unique_ptr<T[]>(new T[m_size]);
        else m_array = nullptr;
    }

    Array (const Array& arr) {
        m_size = arr.m_size;
        if (m_size > 0) {
            m_array = std::unique_ptr<T[]>(new T[m_size]);
            std::copy(arr.m_array.get(), arr.m_array.get() + m_size, m_array.get());
        }
        else {
            m_array = nullptr;
        }
    }

    Array (Array&& arr) noexcept {
        m_size = std::move(arr.m_size);
        m_array = std::move(arr.m_array);
    }

    ~Array () noexcept = default;

    Array& operator= (Array other) {
        std::swap(this->m_size, other.m_size);
        std::swap(this->m_array, other.m_array);
        return *this;
    }

    size_t size () const {
        return m_size;
    }

    T& operator[] (const size_t index) {
        assert(index < m_size);
        return m_array[index];
    }
};

