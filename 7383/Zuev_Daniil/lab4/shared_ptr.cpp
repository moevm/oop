template <typename T>
class shared_ptr
{
    template <typename Y>
    friend class shared_ptr;
public:
    explicit shared_ptr(T *ptr = 0):m_ptr(ptr),m_count(m_ptr?new long(1):nullptr)
    {
    }

    ~shared_ptr()
    {
        if(m_count)
        {
            if((*m_count) == 1)
            {
                delete m_ptr;
                delete m_count;
            }
            else
            {
                (*m_count)--;
            }
        }
    }

    shared_ptr(const shared_ptr & other):m_ptr(other.m_ptr),m_count(other.m_count)
    {
        if(m_count)
            (*m_count)++;
    }

    template <typename Y>
    shared_ptr(const shared_ptr<Y> & other) : m_ptr(other.m_ptr), m_count(other.m_count)//Y неявно преобразуется в T
    {
        if (m_count)
            (*m_count)++;
    }

    template <typename Y>
    shared_ptr& operator=(const shared_ptr<Y> & other)
    {
        shared_ptr p(other);
        swap(p);
        return *this;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        shared_ptr tmp(other);
        swap(tmp);
        return *this;
    }

    explicit operator bool() const
    {
        return m_ptr != nullptr;
    }

    T* get() const
    {
        return m_ptr;
    }

    long use_count() const
    {
        return (m_count ? (*m_count) : 0);
    }

    T& operator*() const
    {
        if(m_ptr)
            return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(m_ptr, x.m_ptr);
        std::swap(m_count, x.m_count);
    }

    void reset(T *ptr = 0)
    {
        if(m_count)
        {
            if((*m_count) == 1)
            {
                delete m_ptr;
                delete m_count;
            }
            else
            {
                (*m_count)--;
            }
        }
        m_ptr = ptr;
        m_count = m_ptr ? new long(1) : nullptr;
    }

    template <typename Y>
    bool operator==(const shared_ptr<Y> &other) const
    {
        return (m_ptr == other.m_ptr);
    }

  private:
      T* m_ptr;
      long* m_count;
}
