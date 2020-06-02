#include "pch.h"
#include "Adapter.h"


Adapter::Adapter(Proxy* write) : _write(write) {}

bool Adapter::request(std::string str){
	this->_write->specificRequest(str);
	return true;
}

