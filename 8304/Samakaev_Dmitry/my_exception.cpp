#include "my_exception.h"

const char* my_exception::what() const noexcept
{
	return data.c_str();
}
