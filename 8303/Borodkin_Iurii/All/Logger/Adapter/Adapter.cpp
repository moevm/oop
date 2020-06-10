#include "Adapter.h"

std::string Target::request(const std::string &str)
{
    return str;
}

unsigned long long Adaptee::counter = 0;

std::string Adapter::request(const std::string &str)
{
    return adaptee->specificRequest(str);
}

Adapter::~Adapter()
{
    delete adaptee;
}

std::string Adaptee::specificRequest(const std::string& str)
{
    return std::to_string(++counter) + ": " + str;
}
