#pragma once
#include <string>
class User
{
public:
	User(std::string name);
	std::string getName();
protected:
	std::string _name;
};

