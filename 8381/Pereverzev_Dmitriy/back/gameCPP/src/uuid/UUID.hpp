

#ifndef uuid_hpp
#define uuid_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

class UUID
{
private:
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
    uint32_t t;

    const std::string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    uint32_t xor128(void);

public:
    UUID();
    std::string generateUUID();
};
#endif /* uuid_hpp */
