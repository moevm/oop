#pragma once
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream> 
namespace stepik
{
	
		template <typename Type>
		class vector
		{
		public:
			typedef Type* iterator;
			typedef const Type* const_iterator;

			typedef Type value_type;

			typedef value_type& reference;
			typedef const value_type& const_reference;

			typedef std::ptrdiff_t difference_type;

			explicit vector(size_t count = 0)
			{

				if (count == 0)
				{
					m_first = nullptr;
					m_last = nullptr;
				}
				else
				{
					try_increase_speed(count);
					
				}

			
			}

			template <typename InputIterator>
			vector(InputIterator first, InputIterator last)
				:vector(last - first)//i am understand now 
			{
				

				std::copy(first, last, m_first);


			
			}

			vector(std::initializer_list<Type> init)
				: vector(init.begin(), init.end())
			{

				
			}


			vector(const vector &other)  
			{
				try_increase_speed(other.size());
			
				try {
					
					std::copy(other.m_first, other.m_last, m_first);
				}
				catch (...)
				{
					delete[] m_first;
					throw;
				}


			
			}

			vector(vector&& other)

			{
				m_first = other.m_first;
				m_last = other.m_last;
				other.m_first = nullptr;
				other.m_last = nullptr;
			
			}

			~vector()
			{
				delete[] m_first;
				
			}

		

			reference at(size_t pos)
			{
				return checkIndexAndGet(pos);
			}

			const_reference at(size_t pos) const
			{

				return checkIndexAndGet(pos);
			}
			vector& operator=(const vector& other)
			{
				if (this != &other)   //same or not ?   
				{
					delete[] m_first;
					m_first = new Type[other.size()];
					m_last = m_first + other.size();

					std::copy(other.m_first, other.m_last, m_first);
				}
				return *this;

				
			}

			vector& operator=(vector&& other)
			{
				if (this != &other) {
					delete[] m_first;
					m_first = other.m_first;
					m_last = other.m_last;
					other.m_first = nullptr;
					other.m_last = nullptr;
				}
				return *this;

			
			}
			 void resize(size_t count)
    {
       Type * newType =new Type [count];
        if (size()>=count) {
            std::copy(m_first,m_first+count,newType);
        }
        else {
            std::copy(m_first,m_first+size(),newType);
          
            
            std::fill(newType+size(),newType+count,0);   
        }
            delete[] m_first;
			m_first = newType;
			m_last = m_first + count;		
    
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
         return erase(pos,pos+1);  
        //≈сли посмотреть по примеру http://en.cppreference.com/w/cpp/container/vector/eras 
     
    
    }

    iterator erase(const_iterator first, const_iterator last)
    { int sizet = last - first;
         if (sizet<0)
            throw std::invalid_argument ("last<first ");
       // iterator NoconstFirst= const_cast<iterator> (first);// приводим const_iterator к iterator;
        for (iterator it=(iterator) first ;it<m_last;it++)
            *it=*(it+sizet);
        m_last=m_last-sizet;
        
        return (iterator) first;

    }

			// assign method

			template <typename InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				delete[] m_first;
				size_t count = last - first;
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(first, last, m_first);

				
			}

			//[] operators

			reference operator[](size_t pos)
			{
				return m_first[pos];
			}

			const_reference operator[](size_t pos) const
			{
				return m_first[pos];
			}

			//*begin methods

			iterator begin()
			{
				return m_first;
			}

			const_iterator begin() const
			{
				return m_first;
			}

			//*end methods
			iterator end()
			{
				return m_last;
			}

			const_iterator end() const
			{
				return m_last;
			}

			//size method

			size_t size() const
			{
				return m_last - m_first;
			}

			//empty method
			bool empty() const
			{
				return m_first == m_last;
			}
		
			iterator insert(const_iterator pos, const Type& value)
			{
				//Type values=const_cast<Type> (value);
				
				iterator test = (iterator)& value;
				return insert(pos, test, test + 1);
			
			}

			template <typename InputIterator>
			iterator insert(const_iterator pos, InputIterator first, InputIterator last)
			{
				int count = last - first;
				int Newsize = count + size();
				Type * newType = new Type[Newsize];
				std::copy(m_first, (iterator)pos, newType);
				int sizeFpart = pos - m_first;
				int Fcount = 0;
			
				for (int i = sizeFpart; i<Newsize; i++)
				{
					newType[i] = first[Fcount];
					++Fcount;
				}
				
				for (int q = sizeFpart + count; q<Newsize; q++)
				{
					newType[q] = m_first[q - count];
				}
				delete[] m_first;
				m_first = newType;
				m_last = newType + Newsize;
				return m_first + sizeFpart;

			
			}

			
			void push_back(const value_type& value)
			{
				insert(m_last, value);
			
			}


		private:
			reference checkIndexAndGet(size_t pos) const
			{
				if (pos >= size())
				{
					throw std::out_of_range("out of range");
				}

				return m_first[pos];
			}
			
	
			void    try_increase_speed(size_t count_size)
			{
				m_first = new Type[count_size + 1];
				m_last = m_first + count_size;
			}
			iterator m_first;
			iterator m_last;

		};
	
} // namespace stepik//