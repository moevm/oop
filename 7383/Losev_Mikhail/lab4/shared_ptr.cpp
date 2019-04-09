#include <iostream>
#include <algorithm>

namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
		template <typename D>
		friend class shared_ptr;
		// public methods
		explicit shared_ptr(T *ptr = nullptr) {
			set(ptr);
		}

		~shared_ptr() {
			if (p_control_block != nullptr) 
				if (p_control_block->count == 1) {
					delete p_control_block->ptr;
					delete p_control_block;
				}
				else 
					p_control_block->count -= 1;
		}



		shared_ptr(const shared_ptr & other) {
			p_control_block = other.p_control_block;
			if (p_control_block)
				p_control_block->count += 1;
		}
        template <typename D>
		shared_ptr(const shared_ptr<D> & other) {
			p_control_block = reinterpret_cast <shared_ptr<T>::control_block *> (other.p_control_block);
			// using reinterpret_cast cause p_control_block is not dynamic
			if (p_control_block)
				p_control_block->count += 1;
		}
        
        /*
		shared_ptr& operator=(const shared_ptr & other) {
			if (p_control_block != other.p_control_block) {
				this->~shared_ptr();
				p_control_block = other.p_control_block;
				if (p_control_block != nullptr)
					p_control_block->count += 1;
			}
			return *this;
		}
        */
		
		template <typename D>
		shared_ptr& operator=(const shared_ptr<D> & other)
		{
			if (p_control_block != reinterpret_cast <shared_ptr<T>::control_block *> (other.p_control_block)) {
				this->~shared_ptr();
				p_control_block = reinterpret_cast <shared_ptr<T>::control_block *> (other.p_control_block);
				if (p_control_block != nullptr)
					p_control_block->count += 1;
			}
			return *this;
		}

		template <class D>
		bool operator==(const shared_ptr<D> & ptr2) const {
			return dynamic_cast<D*>(get()) == ptr2.get();
		}

		template <class D>
		bool operator<(const shared_ptr<D> & ptr2) const {
			return dynamic_cast<D*>(get()) < ptr2.get();
		}

		template <class D>
		bool operator!=(const shared_ptr<D> & ptr2) const {
			return !(*this == ptr2);
		}

		template <class D>
		bool operator<=(const shared_ptr<D> & ptr2) const {
			return *this == ptr2 || *this < ptr2;
		}

		template <class D>
		bool operator>(const shared_ptr<D> & ptr2) const {
			return ptr2 < *this;
		}

		template <class D>
		bool operator>=(const shared_ptr<D> & ptr2) const {
			return *this > ptr2 || *this == ptr2;
		}

		explicit operator bool() const {
			return p_control_block != nullptr;
		}

		T* get() const {
			return p_control_block ? p_control_block->ptr : nullptr;
		}

		long use_count() const {
			return p_control_block ? p_control_block->count : 0;
		}

		T& operator*() const {
			if (p_control_block)
				return *p_control_block->ptr;
		}

		T* operator->() const {
			return get();
		}

		void swap(shared_ptr& x) noexcept {
			std::swap(p_control_block, x.p_control_block);
		}

		void reset(T *ptr = 0) {
			this->~shared_ptr();
			set(ptr);	
		}

	private:
		// private methods
		void set(T *ptr) {
			if (ptr != nullptr) {
				p_control_block = new control_block; 
				p_control_block->ptr = ptr;
				p_control_block->count = 1;
			 }
		 	else p_control_block = nullptr;
		}

		// private fields
		struct control_block {
			T *ptr;
			unsigned int count;
		} *p_control_block;
	};	

} // namespace stepik



// Механизм динамической идентификации типа данных доступен только для полиморфных 
// классов (т.е. классов, содержащих хотя бы одну виртуальную функцию-член)

class A
{

public:
	virtual void set(int a) {

	}
};

class B : public A
{
public:
	static int a = 5;
	void set(int b) {A::set(b); a = b;}
	void methodSpecificToB() {

	}
};

using namespace stepik;
using namespace std;

int main() {
	A * a = new B();
	a->a;
	shared_ptr <A> pa1(new A);
	shared_ptr <B> pb(new B);
	shared_ptr <A> pa2(pb);
	shared_ptr <A> pa3(pa1);
	pa3 = pb;


	cout << pa1.use_count() << endl;
	cout << pa2.use_count() << endl;
	cout << pa3.use_count() << endl;

	if (pa3 == pb)
		cout << "pa3 == pb"  << endl;
	if (pa2 == pb)
		cout << "pa2 == pb"  << endl;
	if (pa1 != pb)
		cout << "pa1 != pb"  << endl;
	if (pa1 < pb)
		cout << "pa1 < pb"  << endl;
	if (pb < pa1)
		cout << "pa1 > pb"  << endl;
	if (pa1 <= pb)
		cout << "pa1 <= pb"  << endl;
	

	if (!false)
		return !true;
}