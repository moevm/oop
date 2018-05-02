#include "list.hpp"

#include <iostream>

int main( void )
{
	stepik::list<int> lis;
	//Exception checking
	lis.clear();
	lis.erase(lis.begin());
	lis.push_back(2);
	lis.erase(lis.end());
	
	lis.push_back(2);
	lis.push_front(2);
	lis.pop_front();
	lis.pop_back();
	lis.pop_front();
	lis.pop_back();
	
	lis.push_back(2);
	lis.push_back(2);
	stepik::list<int> sil(lis);
	sil.clear();
	sil = lis;
	sil.print();
	return 0;

}