#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <ctime>
#include <fstream>
#include <string> 
using namespace std;

class logger {
public:
	static int ForCout;
	static string name;
	void static set_name();
	void static add(string s); 
	void static file(string s);
	void static console(string s);
};
string f();