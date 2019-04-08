#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
  
using namespace std;

template <typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
        cout << "(default) constructor" << endl;
    }

	// copy constructor
	Array(const Array& arr) : m_size(arr.m_size)
		, m_array(m_size ? new T[m_size]() : nullptr) {
		cout << "copy constructor" << endl;
		try {
			for (size_t i = 0; i < m_size; ++i) {
				m_array[i] = arr.m_array[i];
			}
		}
		catch (...) {
			delete[] m_array;
			throw;
		}
	}

	// move constructor
	Array(Array&& arr) : m_size(arr.m_size)
		, m_array(arr.m_array) {
		cout << "move constructor" << endl;
		arr.m_array = nullptr;
		arr.m_size = 0;
	}

	// copy assignment operator
	Array& operator =(const Array& arr) {
		cout << "copy assignment operator" << endl;
        Array tmp(*this);
		m_size = arr.m_size;
		m_array = new T[m_size];
		for (size_t i = 0; i < m_size; ++i) {
			m_array[i] = arr.m_array[i];
		}
		return *this;
	}

	// move assignment operator
	Array & operator=(Array &&arr) {
        cout << "move assignment operator" << endl;
		if (this != &arr) {
			delete[] m_array;
			m_size = arr.m_size;
			m_array = arr.m_array;
			arr.m_array = nullptr;
			m_size = 0;
		}
		return *this;
	}

	const size_t size() const {
		return m_size;
	}

	T& operator [](const size_t index) {
		assert(index < m_size);
		return m_array[index];
	}

	~Array() {
		delete[] m_array;
	}

private:
	size_t m_size;
	T* m_array;
};

template<typename T>
void go(T&& arg)
{
	if (is_reference<T>::value)
	{
		cout << "l-value" << endl;
	}
	else
	{
		cout << "r-value" << endl;
	}
}

template <class T>
T fun(T&& a){
	return T(forward <T> (a));
}

Array fu( Array a){
	return Array a;
}

int main()
{
	Array  b;
	fu(b);
	//Array  a = b;
	fu(move(b));
	Array  c = move(b);
	fu(5);

	system("pause");
	return 0;
}

using namespace std;
class A
{
public:
A()
{

}
A(const A&)
{
cout<< "Copy"<< endl;
}
A(A&&)
{
cout<< "Move"<< endl;
}
};

A go(A arg)
{ 
return A (arg);
}

A get(){
A a;
return a;
} 
//void go (A a){}

int main()
{
A a;
go(a);
go(A{});

return 0;
}
