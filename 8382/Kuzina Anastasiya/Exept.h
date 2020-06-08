#pragma once
#include <iostream>
#include <string>



class except : public std::exception {
public:
	except(std::string e);
	   	 
};
