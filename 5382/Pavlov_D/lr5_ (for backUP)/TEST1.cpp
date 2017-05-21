// TEST1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
//#include "lr2.h"
//#include <gtest/gtest.h>
#include "RightTriangle.h"
#include "Square.h"
#include "IsoscelesTriangle.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include "vectorStepik.h"
#include "SharedPtrStepik.h"
using namespace std;

int main(int argc,char* argv[])
{
	stepik::vector<int> v(2);
	v[0] = 1;
	v[1] = 2;
	int value = 10;
	v.push_back(value);
	std::cout << v[2] << std::endl;
	std::cout << v.size() << std::endl;
	v.erase(v.end());
	std::cout << v.size() << std::endl;
	system("pause");

    return 0;
}

