namespace stepik
{
    template <typename T>
    class shared_ptr
    {
        template <typename D>
        friend class shared_ptr;
    public:
        explicit shared_ptr(T *ptr = 0) : ptr(ptr), counter(new int(1))
        {
            // implement this
        }
        
        ~shared_ptr()
        {
            del();// implement this
        }
        
        shared_ptr(const shared_ptr & other) : ptr(other.ptr), counter(other.counter)
        {
            ++(*counter);// implement this
        }
        
        template <typename D>
        shared_ptr(const shared_ptr<D> & other) : ptr(other.ptr), counter(other.counter)
        {
            ++(*counter);
        }
        
        shared_ptr& operator=(const shared_ptr & other)
        {
            if(other.ptr != ptr){
                del();
                ptr = other.ptr;
                counter = other.counter;
                ++(*counter);
            }
            return *this;// implement this
        }
        
        template <typename D>
        shared_ptr& operator=(const shared_ptr<D> & other)
        {
            if(other.ptr != ptr){
                del();
                ptr = other.ptr;
                counter = other.counter;
                ++(*counter);
            }
            return *this;
        }
        
        explicit operator bool() const
        {
            return ptr != nullptr;// implement this
        }
        
        template <typename D>
        bool operator == (const shared_ptr<D> & other) const
        {
            return ptr == other.ptr;
        }
        
        template <typename D>
        bool operator != (const shared_ptr<D> & other) const
        {
            return !(ptr == other.ptr);
        }
        
        T* get() const
        {
            return ptr;// implement this
        }
        
        int use_count() const
        {
            return ptr == nullptr ? 0 : *counter;// implement this
        }
        
        T& operator*() const
        {
            return *ptr;// implement this
        }
        
        T* operator->() const
        {
            return ptr;// implement this
        }
        
        void swap(shared_ptr& x) noexcept
        {
            T* tmp = ptr;
            int* tmp_c = counter;
            ptr = x.ptr;
            counter = x.counter;
            x.ptr = tmp;
            x.counter = tmp_c;// implement this
        }
        
        void reset(T *ptr = 0)
        {
            del();
            this->ptr = ptr;
            this->counter = new int(1);// implement this
        }
        
    private:
        T* ptr;
        int* counter;
        void del(){
            if(ptr != nullptr){
                if(*counter == 1){
                    delete counter;
                    delete ptr;
                }else
                    --(*counter);// implement this
            }
        }// data members
    };
} // namespace stepik
