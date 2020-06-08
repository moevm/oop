#include <iostream>
#include <memory>
#ifndef GAME
#define GAME
#include "game.cpp"
#endif
using namespace std;

int main()
{
    Game game(10, 10, 30);
    return 0;
}
