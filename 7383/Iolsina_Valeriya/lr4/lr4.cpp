namespace stepik
{
  template <typename T>
  class shared_ptr
  {
    template <typename T2>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0) : m_ptr(ptr), count(ptr ? new long(1) : nullptr)
    { }

    ~shared_ptr()
    {
      if(m_ptr)
          delete_ptr();
    }

    shared_ptr(const shared_ptr & other) : m_ptr(other.m_ptr), count(other.count) //конструктор копирования
    {
      if(count)
          (*count)++;
    }

    template <typename T1>
    shared_ptr(const shared_ptr<T1> & other) : m_ptr(other.m_ptr), count(other.count)
    {
      if(count)
          (*count)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
       if(m_ptr != other.m_ptr)
       {
          if(m_ptr)
              delete_ptr();
          m_ptr=other.m_ptr;
          count=other.count;
          if(m_ptr)
              (*count)++;
      }
      return *this;
    }

    template <typename T1>
    shared_ptr& operator=(const shared_ptr<T1> & other)
    {
      if(m_ptr!=other.m_ptr)
      {
          if(m_ptr)
              delete_ptr();
          m_ptr=other.m_ptr;
          count=other.count;
          if(m_ptr)
              (*count)++;
      }
      return *this;
    }

    template <typename T1>
    bool operator == (const shared_ptr<T1>& other) const
    {
      return m_ptr==other.m_ptr;
    }

    explicit operator bool() const
    {
      return m_ptr != nullptr;
    }

    T* get() const  //указатель на управляемый объект
    {
      return m_ptr;
    }

    long use_count() const  //количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
    {
       return (count ? *count : 0);
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
      std::swap(m_ptr, x.m_ptr);
      std::swap(count, x.count);
    }

    void reset(T *ptr = 0)  //замена объекта, которым владеет
    {
      if(m_ptr)
          delete_ptr();
      m_ptr = ptr;
      if(m_ptr)
          count = new long(1);
      else
          count = nullptr;
    }

  private:
    T *m_ptr;
    long *count;
    void delete_ptr()
    {
        if((*count)==1)
        {
            delete m_ptr;
            delete count;
        }
        else
            (*count)--;
    }
  };
} // namespace stepik
