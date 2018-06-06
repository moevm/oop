#include "vector.h"

template<typename Type>
template<typename InputIterator>
void vector<Type>::assign(InputIterator first, InputIterator last) 
{
	size_t new_size = last - first;
	if (!empty()) {
		delete[] m_first;
	}
	m_first = new Type[new_size];
	m_last = m_first + new_size;
	std::copy(first, last, m_first);
}

