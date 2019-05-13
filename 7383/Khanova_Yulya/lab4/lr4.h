namespace stepik
{
template <typename T>
class shared_ptr
{
public:
    template <typename D> friend class shared_ptr;
    explicit shared_ptr(T *ptr = 0)
    {
        m_ptr = ptr;
        count = new long(1);
        // implement this
    }

    ~shared_ptr()
    {
        if((*count)>0) {
            (*count)--;
        }
        if((*count)==0) {
            delete m_ptr;
            delete count;
        }
        // implement this
    }

    shared_ptr(const shared_ptr & other)
    {
        m_ptr = other.m_ptr;
        count = other.count;
        if(count) {
            ++(*count);
        }
        // implement this
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if(this != &other) {
            if((*count)>0) {
                (*count)--;
            }
            if((*count)==0) {
                delete m_ptr;
                delete count;
            }
            m_ptr = other.m_ptr;
            count = other.count;
            if(count) {
                ++(*count);
            }
        }
        return *this;
        // implement this
    }

    explicit operator bool() const
    {
        return !(m_ptr == nullptr);
        // implement this
    }

    T* get() const
    {
        return m_ptr;
        // implement this
    }

    long use_count() const
    {
        if (m_ptr)
            return *count;
        return 0;
        // implement this
    }

    T& operator*() const
    {
        return (*m_ptr);
        // implement this
    }

    T* operator->() const
    {
        return m_ptr;
        // implement this
    }

    void swap(shared_ptr& x) noexcept
    {
        shared_ptr tmp(x);
        x.m_ptr = m_ptr;
        x.count = count;
        m_ptr = tmp.m_ptr;
        count = tmp.count;
        // implement this
    }

    void reset(T *ptr = 0)
    {
        shared_ptr p(ptr);
        swap(p);
        // implement this
    }

    template <typename D>
    shared_ptr(const shared_ptr<D> & other) :m_ptr(other.m_ptr), count(other.count)
    {
        if (count) {

            (*count)++;

        }
    }

    template <typename D>
    shared_ptr& operator=(const shared_ptr<D> & other)
    {
        if (m_ptr != other.m_ptr) {

            if ((*count)>0) {
                (*count)--;
            }
            if ((*count) == 0) {
                delete m_ptr;
                delete count;
            }

            m_ptr = other.m_ptr;
            count = other.count;
            (*count)++;
        }
        return *this;
    }

    template <typename D>
    bool operator == (const shared_ptr<D>& other) const {
        return m_ptr == other.m_ptr;
    }
private:
    // data members
    T * m_ptr;
    long*  count;
};
}
// namespace stepik
