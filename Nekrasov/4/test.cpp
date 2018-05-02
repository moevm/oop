#include "shared_ptr.hpp"
#include <iostream>

int main( void )
{
	int* z = new int;
	stepik::shared_ptr<int> b = z;
	stepik::shared_ptr<int> c(b);
	stepik::shared_ptr<int> d;
	d.reset(z);
	d.swap(a);
	return 0;
}