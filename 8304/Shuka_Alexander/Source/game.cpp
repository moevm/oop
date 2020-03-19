#include "game.h"


Game::Game(size_t width, size_t height) :
    gameField(height, width)
{
    isRun = true;
}


void Game::run()
{
    isRun = true;

    while (isRun) {
        COMMAND command = input();
        bool flag = logic(command);
        if (flag) {
            draw();
        }
    }
}


void Game::draw()
{
    system("cls");
    for (size_t i = 0; i < gameField.getHeight(); ++i) {
        for (size_t  j = 0; j < gameField.getWidth(); ++j) {
            if (gameField.getCell(Point2D(j, i))->isEmpty()) {
                std::cout << ". ";
            }
            else {
                std::cout << "U ";
            }
        }
        std::cout << '\n';
    }
}


bool Game::logic(COMMAND command)
{
    switch (command) {
    case COMMAND::UP:
        break;
    case COMMAND::DOWN:
        break;
    case COMMAND::LEFT:
        break;
    case COMMAND::RIGHT:
        break;
    case COMMAND::EXIT:
        isRun = false;
        break;
    case COMMAND::STAY:
        break;
    case COMMAND::ADD_UNIT:
        break;
    }
    return false;
}


COMMAND Game::input()
{
    if (kbhit()) {
        switch (getch()) {
        case 'w':
            return COMMAND::UP;
        case 's':
            return COMMAND::DOWN;
        case 'a':
            return COMMAND::LEFT;
        case 'd':
            return COMMAND::RIGHT;
        case 'e':
            return COMMAND::EXIT;
        case 'r':
            return COMMAND::ADD_UNIT;
        }
    }
    return COMMAND::STAY;
}
