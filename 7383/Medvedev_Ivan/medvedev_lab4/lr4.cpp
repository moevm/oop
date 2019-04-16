namespace stepik
{
  template <typename T>

  class shared_ptr
  {
  template <typename D>
  friend class shared_ptr;
   
      
  public:
    explicit shared_ptr(T *ptr = nullptr) :
          m_ptr(ptr),
          counter(ptr ? new long(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        clear();
    }
      
    template <typename D>
    shared_ptr(const shared_ptr<D> & other) :
        m_ptr(other.m_ptr),
        counter(other.counter)
    {
        if (counter)
            (*counter)++;
    }
     
    shared_ptr(const shared_ptr & other) :
        m_ptr(other.m_ptr),
        counter(other.counter)
    {
        if (counter)
            (*counter)++;
    }
      
    template <typename D>
    shared_ptr& operator=(const shared_ptr<D> & other)
    {
        shared_ptr p(other);
        swap(p);
        return *this;
    }
      
    shared_ptr& operator=(const shared_ptr & other)
    {
        shared_ptr p(other);
        swap(p);
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
        return (counter ? *counter : 0);
    }

    T& operator*() const
    {
        return (*m_ptr);
    }

    T* operator->() const
    {
        return m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(m_ptr, x.m_ptr);
        std::swap(counter, x.counter);
    }
    
    template <typename D>
    bool operator==(const shared_ptr<D> &other) const
    {
        return (m_ptr == other.m_ptr);
    }

    void reset(T *ptr = nullptr)
    {
      clear();
      m_ptr = ptr;
      if(ptr)
        counter = new long(1);
      else
        counter = nullptr;

    }

  private:
    // data members
    T *m_ptr;
    long*counter;


 void clear(){
      if(m_ptr){
          if((*counter) == 1){
              delete m_ptr;
              delete counter;
          }
          else (*counter)--;
      }
    }
  };
}
