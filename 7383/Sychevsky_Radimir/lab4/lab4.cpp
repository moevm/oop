namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    template <typename G>
    friend class shared_ptr;
    explicit shared_ptr(T *ptr = 0): m_ptr(ptr), m_count(ptr ? new size_t(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        del_ptr();
    }

    shared_ptr(const shared_ptr & other): m_ptr(other.m_ptr), m_count(other.m_count)
    {
        if(m_count)
            (*m_count)++;
    }
    
    template <typename G>
    shared_ptr(const shared_ptr<G> & other):m_ptr(other.m_ptr), m_count(other.m_count)
    {
        if(m_count)
            (*m_count)++;
    }
      
    shared_ptr& operator=(const shared_ptr & other)
    {
        shared_ptr tmp_ptr(other);
          swap(tmp_ptr);
          return *this;
    }

    template <typename G>
    shared_ptr& operator=(const shared_ptr<G> & other)
    {
        shared_ptr tmp_ptr(other);
          swap(tmp_ptr);
          return *this;
    }
    
    explicit operator bool() const
    {
        return (m_ptr != nullptr);
    }

    T* get() const
    {
        return m_ptr;
    }

    long use_count() const
    {
        return (m_count ? *m_count : 0);
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        T* tmp_ptr = x.m_ptr;
        size_t* tmp_count = x.m_count;
        x.m_ptr = m_ptr;
        x.m_count = m_count;
        m_ptr = tmp_ptr;
        m_count = tmp_count;
    }

    template <typename G>
    bool operator==(const shared_ptr<G> &other) const
    {
        return (m_ptr == other.m_ptr);
    }
    
    template <typename G>
    bool operator != (const shared_ptr<G> & other) const
    {
        return !(m_ptr == other.m_ptr);
    }
      
    void reset(T *ptr = 0)
    {
        shared_ptr tmp_ptr(ptr);
        swap(tmp_ptr);
        
    }

  private:
    T* m_ptr;
    size_t* m_count;
    void del_ptr(){
        if(m_count){
            (*m_count)--;
            if(*m_count == 0){
                delete m_ptr;
                delete m_count;
            }
        }
    }
  };      
} 