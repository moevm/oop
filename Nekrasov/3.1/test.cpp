#include "vector.hpp"

#include <iostream>

int main(void)
{
	stepik::vector<int> a( {1,2,3,4,5,6,7,8};
	stepik::vector<int> b = a;
	stepik::vector<int> c(std::move(b));
	b.push_back(1);
	b.push_back(3);
	b.push_back(4);
	b.insert(b.begin(), 888);
	b.insert(b.begin() + 3, a, a);
	b.insert(b.begin() + 2, a, a + 3);
	b.erase(b.begin());
	c.resize(2);
	c.resize(2*10);
	c.assign(99,100);
	c.erase(c.begin(),c.end());
	return 0;
}