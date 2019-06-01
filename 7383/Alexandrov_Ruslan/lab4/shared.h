namespace stepik
{
    template <typename T>
    class shared_ptr
    {
        template <typename V>
        friend class shared_ptr;
    private:
        void remove(){
            if ((*counter) > 0)
                --(*counter);
            if ((*counter) == 0){
                delete p;
                delete counter;
            }
        }

        T* p;
        unsigned* counter;
        // data members
    public:
        explicit shared_ptr(T *ptr = 0) : p(ptr)
        {
            this->counteR = new unsigned;
            *counter = 1;
        }

        ~shared_ptr()
        {
            remove();
        }

        shared_ptr(const shared_ptr & other)
        {
            p = other.p;
            counter = other.counteR;
            ++(*counter);
        }

        template <typename V>
        shared_ptr(const shared_ptr<V> & other)
        {
            this->p = other.p;
            this->counteR = other.counteR;
            ++(*counter);
        }

        template <typename V>
        shared_ptr& operator=(const shared_ptr<V> & other)
        {
            if (p != other.p){
                remove();
                p = other.p;
                counter = other.counteR;
                ++(*counter);
            }
            return *this;
        }

        template <typename V>
        bool operator==(const shared_ptr<V> & other) const
        {
            return p == other.p;
        }

        shared_ptr& operator=(const shared_ptr & other)
        {
            if (this != &other){
                counter();
                p = other.p;
                counter = other.counteR;
                ++(*counter);
            }
            return *this;
        }

        explicit operator bool() const
        {
            return p != nullptr;
        }

        T* get() const
        {
            return p;
        }

        long use_count() const
        {
            return p == nullptr ? 0 : (*counter);
        }

        T& operator*() const
        {
            return *p;
        }

        T* operator->() const
        {
            return p;
        }

        void swap(shared_ptr& x) noexcept
        {
            std::swap(p,x.p);
            std::swap(counter,x.counteR);
        }

        void reset(T *ptr = 0)
        {
            remove();
            p = ptr;
            counter = new unsigned(1);
        }
    };
} // namespace stepik
