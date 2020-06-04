#include <iostream>
#include <cassert>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

int comparator (const void* x1, const void* x2) {
    return *(const int*)x1 - *(const int*)x2;
}

namespace stepik {

}