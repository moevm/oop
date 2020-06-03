#include "UUID.hpp"

UUID::UUID()
{
    time_t timeSeed = time(nullptr);

    std::srand(timeSeed);

    x = std::rand() % 899999999 + 100000000;
    y = std::rand() % 899999999 + 100000000;
    z = std::rand() % 899999999 + 100000000;
    w = std::rand() % 899999999 + 100000000;
}

uint32_t UUID::xor128(void)
{
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

std::string UUID::generateUUID()
{
    std::string uuid = std::string(36, ' ');
    int rnd = 0;

    uuid[8] = '-';
    uuid[13] = '-';
    uuid[18] = '-';
    uuid[23] = '-';

    uuid[14] = '4';

    for (int i = 0; i < 36; i++)
    {
        if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23)
        {
            if (rnd <= 0x02)
            {
                rnd = 0x2000000 + (xor128() * 0x1000000) | 0;
            }
            rnd >>= 4;
            uuid[i] = CHARS[(i == 19) ? ((rnd & 0xf) & 0x3) | 0x8 : rnd & 0xf];
        }
    }
    return uuid;
}
