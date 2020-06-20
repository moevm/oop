#include <iostream>

#include "demo.hpp"

int
main(void)
{
    demo::DemoSession sess {};
    sess.run(std::cin, std::cout);
    return 0;
}
