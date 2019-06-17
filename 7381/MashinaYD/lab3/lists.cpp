#include "pch.h"
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>
//namespace stepik
//{
	template <class Type>
	struct node
	{
		Type value;
		node* next;
		node* prev;

		node(const Type& value, node<Type>* next, node<Type>* prev)
			: value(value), next(next), prev(prev)
		{
		}
	};

	template <class Type>
	class list;

	template <class Type>
	class list_iterator
	{
	public:
		friend class list<Type>;

		typedef ptrdiff_t difference_type;
		typedef Type value_type;
		typedef Type* pointer;
		typedef Type& reference;
		typedef size_t size_type;
		typedef std::forward_iterator_tag iterator_category;

		list_iterator()
			: m_node(nullptr)
		{
		}

		list_iterator(node<Type>* p)
			: m_node(p)
		{
		}

		list_iterator(const list_iterator& other)
			: m_node(other.m_node)
		{
		}

		list_iterator& operator=(const list_iterator& other)
		{
			m_node = other.m_node;
			return (*this);
		}

		bool operator == (const list_iterator& other) const
		{
			return (m_node == other.m_node);
		}

		bool operator != (const list_iterator& other) const
		{
			return (m_node != other.m_node);
		}

		reference operator * ()
		{
			return (m_node->value);
		}

		pointer operator->()
		{
			return (m_node);
		}

		list_iterator& operator++()
		{
			m_node = m_node->next;
			return (*this);
		}

		

		list_iterator operator++(int)
		{
			if(m_node!=nullptr){
				list_iterator* old_iterator = new list_iterator(*this);
				m_node = m_node->next;
				return (*old_iterator);
			}
			return nullptr;
		}

		list_iterator operator--(int)
		{
			list_iterator* old_iterator = new list_iterator(*this);
			m_node = m_node->prev;
			return (*old_iterator);
		}

		list_iterator& operator+=(int i)
		{
			int m = i;
			if (m >= 0)
				while (m--)
					(*this)++;
			else
				while (m++)
					(*this)--;

			return (*this);
		}

		list_iterator& operator-=(int i)
		{
			return ((*this)+=-i);
		}

	private:
		node<Type>* m_node;
	};

	template <class Type>
	class list
	{
	public:
		typedef list_iterator<Type> iterator;
		typedef Type value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;

		list() : m_head(nullptr), m_tail(nullptr), m_size(0)
		{
		}

		~list()
		{
			clear();
		}

		list(const list& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
		{
			for (node<Type>* Pnode = other.m_head; Pnode; Pnode = Pnode->next)
				push_back(Pnode->value);
		}

		list(list&& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
		{
			std::swap(m_head, other.m_head);
			std::swap(m_tail, other.m_tail);
			std::swap(m_size, other.m_size);
		}

		list& operator=(const list& other)
		{
			clear();
			for (node<Type>* Pnode = other.m_head; Pnode; Pnode = Pnode->next)
				push_back(Pnode->value);
			return (*this);
		}

		list& operator=(list&& other)
		{
			std::swap(m_head, other.m_head);
			std::swap(m_tail, other.m_tail);
			std::swap(m_size, other.m_size);
			return (*this);
		}

		iterator insert(iterator pos, const Type& value)
		{
			node<Type>* Pnode = pos.m_node;
			if (Pnode == nullptr)
			{
				push_back(value);
				return iterator(m_tail);
			}
			else if (Pnode->prev == nullptr)
			{
				push_front(value);
				return iterator(m_head);
			}
			node<Type>* new_node = new node<Type>(value, Pnode, Pnode->prev);
			Pnode->prev->next = new_node;
			Pnode->prev = new_node;
			++m_size;
			return iterator(new_node);
		}

		iterator erase(iterator pos)
		{
			node<Type>* Pnode = pos.m_node;

			if (Pnode == nullptr)
				return pos;

			if (Pnode->prev == nullptr)
			{
				pop_front();
				return iterator(m_head);
			}

			if (Pnode->next == nullptr)
			{
				pop_back();
				return iterator();
			}

			node<Type>* Pnext = Pnode->next;
			Pnode->next->prev = Pnode->prev;
			Pnode->prev->next = Pnode->next;
			delete Pnode;
			--m_size;
			return iterator(Pnext);
		}

		void push_back(const value_type& value)
		{
			node<Type>* new_node = new node<Type>(value, nullptr, m_tail);
			if (m_size == 0)
			{
				m_head = m_tail = new_node;
			}
			else
			{
				m_tail->next = new_node;
				m_tail = new_node;
			}
			++m_size;
		}

		void push_front(const value_type& value)
		{
			node<Type>* new_node = new node<Type>(value, m_head, nullptr);
			if (m_size == 0)
			{
				m_head = m_tail = new_node;
			}
			else
			{
				m_head->prev = new_node;
				m_head = new_node;
			}
			++m_size;
		}

		void pop_front()
		{
			--m_size;
			node<Type>* new_head = m_head->next;
			delete m_head;
			m_head = new_head;
			if (m_size == 0)
			{
				m_tail = nullptr;
			}
			else
			{
				m_head->prev = nullptr;
			}
		}

		void pop_back()
		{
			--m_size;
			node<Type>* new_tail = m_tail->prev;
			delete m_tail;
			m_tail = new_tail;
			if (m_size == 0)
			{
				m_head = nullptr;
			}
			else
			{
				m_tail->next = nullptr;
			}
		}

		void clear()
		{
			node<Type>* Pnode = m_head;
			node<Type>* Pnext;
			while (Pnode)
			{
				Pnext = Pnode->next;
				delete Pnode;
				Pnode = Pnext;
			}
			m_head = m_tail = nullptr;
			m_size = 0;
		}

		reference front()
		{
			return (m_head->value);
		}

		const_reference front() const
		{
			return (m_head->value);
		}

		reference back()
		{
			return (m_tail->value);
		}

		const_reference back() const
		{
			return (m_tail->value);
		}

		bool empty() const
		{
			return (!m_size);
		}

		size_t size() const
		{
			return (m_size);
		}

		iterator begin() const
		{
			return iterator(m_head);
		}

		iterator end() const
		{
			return iterator();
		}

	private:
		node<Type>* m_head;
		node<Type>* m_tail;
		size_t m_size;
	};
//}// namespace stepik

	template <class Type>
	void PrintList(list_iterator<Type> i) {
		while (i != nullptr) {
			std::cout << *i ;
			i++;
			if(i!=nullptr)
				std::cout << ", ";
		}
	}

	int main() {
		list <int> list1, list2, list3;
		list1.push_front(1);
		list1.push_back(2);
		list1.push_front(3);

		list2.push_front(1);
		list2.push_front(2);
		list2.push_front(3);
		list2.push_front(4);
		list2.push_front(5);
		list2.push_front(6);
		list2.push_front(7);
		list2.push_front(8);
		list2.push_front(9);
		list2.push_front(10);

		std::cout << "erasing these elements from list1:\n";

		list_iterator<int>  i, q;
		i = list1.begin();
		while (!list1.empty()) {
			std::cout << *i << "\n";
			q = i;
			i++;
			list1.erase(q);
		}
		std::cout << "list1 looks like\n";
		PrintList(list1.begin());
		std::cout << "\n---------\n";

		std::cout << "list2 looks like\n";
		PrintList(list2.begin());

		list3.push_back(11);
		list3.push_back(12);
		list3.push_back(13);
		list3.push_back(14);
		list3.push_back(15);
		list3.push_back(16);
		list3.push_back(17);
		list3.push_back(18);
		list3.push_back(19);
		list3.push_back(20);

		std::cout << "\n-------------\n";

		std::cout << "erasing these elements from list3:\n";

		i = list3.begin();
		while ((!list3.empty()) && i != nullptr) {
			std::cout << *i << "\n";
			q = i;
			i += 2;
			list3.erase(q);
		}

		std::cout << "list3 now looks like\n";

		i = list3.begin();
		PrintList<int>(i);

		std::cout << "\n-------------\n";

		list<char> list4;

		list4.push_back('a');
		list4.push_back('b');
		list4.push_back('c');
		list4.push_back('d');
		list4.push_back('e');
		list4.push_back('f');
		list4.push_back('g');
		list4.push_back('h');
		list4.push_back('i');
		list4.push_back('j');
		std::cout << "\nlist4 looks like\n";
		PrintList(list4.begin());
		list_iterator<char> v = list4.begin();
		size_t n = 0, answer = 1;
		while (answer==1) {
			std::cout << "\nDo you want to look at the members of list4 separately?\n1 stands for 'yes', 0 for 'no'";
			std::cin >> answer;
			if (answer==1) {
				std::cout << "Which member of list4 do you want to see?\n";
				std::cin >> n;
				v = list4.begin();
				v += n-1;//remove -1 if indexes are implied
				if (v != nullptr) {
					std::cout << "\nIt's " << *v << "\n";
				}
				else
					std::cout << "\nNo such element\n";
			}
		}
		std::cout << "\n-------------\n";
		answer = 0;
		list <int> yourlist;
		list_iterator<int> iter = yourlist.begin();
		std::cout << "\nWanna create and edit your own list of integers?\n1-yes\n0-no\n";
		std::cin >> answer;

		if (answer==1) {
			answer=0;
			std::cout << "\nHow many items will there be in your list?\n";
			std::cin >> answer;
			int value = 0;
			for (size_t w = 0; w < answer; w++) {
				std::cout << "\nEnter value number "<< w+1<<":\n";
				std::cin >> value;
				yourlist.push_back(value);
			}
			std::cout << "\nThis is yout list:\n";
			PrintList(yourlist.begin());
			answer = 1;
			while (answer==1) {
				std::cout << "\nDo you want to edit it?\n1-yes\n0-no\n";
				std::cin >> answer;
				if (answer == 1) {
					answer = 0;
					std::cout << "\n1-erase a certain item\n2-change a certain item\n";
					std::cin >> answer;
					switch (answer) {
					case 1:
						std::cout << "\nWhich item do you want to erase?\n";
						answer = 0;
						std::cin >> answer;
						iter = yourlist.begin()+=answer-1;
						yourlist.erase(iter);
						std::cout << "\nNow your list looks like this:\n";
						PrintList(yourlist.begin());
						break;
					case 2:
						std::cout << "\nWhich item do you want to change?\n";
						answer = 0;
						std::cin >> answer;
						iter = yourlist.begin() += answer-1;
						std::cout << "\nIt's item '" << *iter << "'. What value do you want to change it to?";
						answer = 0;
						std::cin >> answer;
						*iter = answer;
						std::cout << "\nNow your list looks like this:\n";
						PrintList(yourlist.begin());
						break;
					default:
						break;
					}
					answer = 1;
				}
				
			}
			

		}
		

	return 0;
}