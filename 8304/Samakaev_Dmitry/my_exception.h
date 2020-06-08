#pragma once
#include <exception>
#include <string>

class my_exception:public std::exception
{
	std::string data;
public:
	const char* what() const noexcept;
	my_exception(std::string const& data) {
		this->data = data;
	}
};

