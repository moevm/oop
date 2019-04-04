#pragma once
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

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
			allocate(count);
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			allocate(last - first);
			std::copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init)
		{
			allocate(init.end() - init.begin());
			std::copy(init.begin(), init.end(), m_first);
		}

		vector(const vector& other)
		{
			allocate(other.size());
			std::copy(other.begin(), other.end(), m_first);
		}

		vector(vector&& other)
		{
			m_first = m_last = iterator();
			std::swap(other.m_first, m_first);
			std::swap(other.m_last, m_last);
		}

		~vector()
		{
			tidy_up();
		}

		//assignment operators
		vector& operator=(const vector& other)
		{
			assign(other.begin(), other.end());
			return (*this);
		}

		vector& operator=(vector&& other)
		{
			tidy_up();
			std::swap(m_first, other.m_first);
			std::swap(m_last, other.m_last);
			return (*this);
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			tidy_up();
			if (allocate(last - first)) {
				std::copy(first, last, m_first);
			}
		}

		//resize method
		void resize(size_t count)
		{
			if (count > size()) {
				iterator new_arr = new value_type[count];
				std::copy(m_first, m_first + size(), new_arr);
				for (size_t i = size(); i < count; i++) {
					new_arr[i] = value_type();
				}
				tidy_up();
				m_first = new_arr;
				m_last = m_first + count;
			}
			else {
				m_last -= size() - count;
			}
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			std::rotate(iterator(pos), iterator(pos) + 1, end());
			resize(size() - 1);
			return iterator(pos);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			difference_type dist = std::distance(first, last);
			std::rotate(iterator(first), iterator(last), end());
			resize(size() - dist);
			return iterator(first);
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			difference_type offset = std::distance(begin(), iterator(pos));
			resize(size() + 1);
			iterator new_pos = begin() + offset;
			std::rotate(new_pos, end() - 1, end());
			*new_pos = value;
			return new_pos;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			difference_type offset = std::distance(begin(), iterator(pos));
			difference_type length = last - first;
			resize(size() + length);
			iterator new_pos = begin() + offset;
			std::rotate(new_pos, end() - length, end());
			std::copy(first, last, new_pos);
			return new_pos;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			resize(size() + 1);
			*(m_last - 1) = value;
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

	private:
		reference checkIndexAndGet(size_t pos) const
		{
			if (pos >= size())
			{
				throw std::out_of_range("out of range");
			}

			return m_first[pos];
		}

		//your private functions

		void tidy_up() {
			delete[] m_first;
			m_first = m_last = iterator();
		}

		bool allocate(size_t new_capacity) {
			m_first = m_last = iterator();
			if (!new_capacity)
				return false;
			m_first = new value_type[new_capacity];
			m_last = m_first + new_capacity;
			return true;
		}
	private:
		iterator m_first;
		iterator m_last;
	};
}// namespace stepik