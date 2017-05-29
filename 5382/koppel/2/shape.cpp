#include "stdafx.h"
#include "shape.h"
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

size_t Shape::counter = 0;

ostream &operator << (ostream &ost, Shape& Object)
{
	Object.print(ost);
	return ost;
}

bool Shape::common_vertex(const Shape& other) const
{
	if (std::find_first_of(vertex.begin(), vertex.end(), other.get_vector().begin(), other.get_vector().end()) != vertex.end() ) return true;
	else return false;
}
