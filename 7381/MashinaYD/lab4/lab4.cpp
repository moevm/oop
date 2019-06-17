namespace stepik
{
	template <typename T>
	class shared_ptr
	{
  	public:

	  	using value_type = T;
		using reference = T&;
		using pointer = T*;

		template <class U>
		friend class shared_ptr;

		// 
		explicit shared_ptr(T *ptr = 0)
		: m_ptr(ptr), m_refsCounter(ptr ? new long(1) : nullptr)
		{
		}

		// 
		~shared_ptr()
		{
			if (m_refsCounter)
				dec_refs();
			if (use_count() == 0)
				destroy();
		}

		// 
		shared_ptr(const shared_ptr & other)
		: m_ptr(other.m_ptr), m_refsCounter(other.m_refsCounter)
		{
			if (m_refsCounter)
				inc_refs();
		}
		
		template <class U>
		shared_ptr(const shared_ptr<U> & other)
		: m_ptr(other.m_ptr), m_refsCounter(other.m_refsCounter)
		{
			if (m_refsCounter)
				inc_refs();
		}

		shared_ptr& operator=(const shared_ptr& r)
		{
			shared_ptr(r).swap(*this);
			return (*this);
		}

		template <class U>
		shared_ptr& operator=(const shared_ptr<U>& r)
		{
			shared_ptr(r).swap(*this);
			return (*this);
		}

		// 
		explicit operator bool() const
		{
			return (m_ptr != nullptr);
		}

		// 
		pointer get() const
		{
			return m_ptr;
		}

		//
		long use_count() const
		{
			return (m_refsCounter ? *m_refsCounter : 0);
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(m_ptr, x.m_ptr);
			std::swap(m_refsCounter, x.m_refsCounter);
		}

		void reset(T *ptr = 0)
		{
			if (m_refsCounter)
				dec_refs();
			if (use_count() == 0)
				destroy();
			m_ptr = ptr;
			m_refsCounter = ptr ? new long(1) : nullptr;
		}

	private:

		void dec_refs()
		{
			--*m_refsCounter;
		}

		void inc_refs()
		{
			++*m_refsCounter;
		}

		void destroy()
		{
			if (m_ptr)
				delete m_ptr;
			if (m_refsCounter)
				delete m_refsCounter;
		}

		pointer m_ptr;
		long *m_refsCounter;
	};      
	template <class T, class U>
    bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
	{
		return (lhs.get() == rhs.get());
	}
} // namespace stepik