#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
using namespace std;

//функция компаратор для int
int comp(const void* x1, const void* x2)
{
	return *(const int*)x1 - *(const int*)x2;
}

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
			if (count == 0) {
				m_first = nullptr;
				m_last = nullptr;
			}
			else {
				m_first = new Type[count];
				m_last = m_first + count;
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
			: vector(last - first)
		{
			std::copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init)
			: vector(init.size())
		{
			size_t i = 0;
			for (auto& element : init) {
				m_first[i] = element;
				i++;
			}
		}

		vector(const vector& other)
			: vector(other.begin(), other.end())
		{

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

		//assignment operators
		vector& operator=(const vector& other)
		{
			if (&other != this) {
				size_t size = other.size();
				delete[] m_first;
				m_first = new Type[size];
				std::copy(other.begin(), other.end(), m_first);
				m_last = m_first + size;
			}
			return *this;
		}

		vector& operator=(vector&& other)
		{
			if (&other != this) {
				delete[] m_first;
				m_first = other.begin();
				m_last = other.end();
				other.m_first = nullptr;
				other.m_last = nullptr;
			}
			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			size_t size = last - first;
			delete[] m_first;
			m_first = new Type[size];
			std::copy(first, last, m_first);
			m_last = m_first + size;
		}

		// resize methods
		void resize(size_t count)
		{
			if (count == m_last - m_first)
				return;
			size_t size = this->size();
			Type* data = new Type[size];
			std::copy(m_first, m_last, data);
			delete[] m_first;
			m_first = new Type[count];
			m_last = m_first + count;
			if (count > size) {
				std::copy(data, data + size, m_first);
			}
			else {
				std::copy(data, data + count, m_first);
			}// implement this

			delete[] data;
		}


		iterator erase(const_iterator pos)
		{
			size_t pos_index = pos - m_first;
			for (size_t i = pos_index; i < size() - 1; i++) {
				m_first[i] = m_first[i + 1];
			}
			m_last--;
			resize(size());
			return m_first + pos_index;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			iterator tmp = const_cast<iterator>(first);
			for (size_t i = 0, between = last - first; i < between; ++i) {
				tmp = erase(tmp);
			}
			return tmp;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t size = m_last - m_first;
			size_t ptr = pos - m_first;
            
			Type* data = new Type[size];
			std::copy(m_first, m_last, data);
            delete[] m_first;
            
			m_first = new Type[size + 1];
			m_last = m_first + size + 1;
			std::copy(data, data + ptr, m_first);
            
			*(m_first + ptr) = value;
			std::copy(data + ptr, data + size, m_first + ptr + 1);
			
            delete[] data;
            return m_first + ptr;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t size = m_last - m_first;
			size_t dif = last - first;
			size_t ptr = pos - m_first;
            
            // copy data
			Type* data = new Type[size];
			std::copy(m_first, m_last, data);
			
            delete[] m_first;
            m_first = new Type[size + dif];
			m_last = m_first + size + dif;
			
            std::copy(data, data + ptr, m_first);
			std::copy(first, last, m_first + ptr);
			
            std::copy(data + ptr, data + size, m_first + ptr + dif);
			
            delete[] data;
            return m_first + ptr;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			insert(m_last, value);
		}

		//at methods
		reference at(size_t pos)
		{
			return checkIndexAndGet(pos);
		}

		const_reference at(size_t pos) const
		{
			return checkIndexAndGet(pos);
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

		friend vector operator + (vector& a, vector& b) {
			vector <Type> c(a.size() + b.size());
			std::copy(a.m_first, a.m_last, c.m_first);
			std::copy(b.m_first, b.m_last, c.m_first + a.size());
			return c;
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

	private:
		iterator m_first;
		iterator m_last;
	};
}