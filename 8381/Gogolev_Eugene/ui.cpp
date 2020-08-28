#include "ui.hpp"
#include "tiles/tile.hpp"
#include "units/unit.hpp"

void UI::init (int x, int y) {
    this->sizeX = x;
    this->sizeY = y;
    frame = new char[x * y * 9];
}

void UI::displayTile (int x, int y, Tile* tile) {
    for (int charX = 0; charX < 3; charX++) {
        for (int charY = 0; charY < 3; charY++) {
            frame[toIndex(x, y, charX, charY)] = tile->getChar(charX, charY);
        }
    }
}

void UI::displayUnit (Unit* unit) {
    for (int charX = 0; charX < 3; charX++) {
        for (int charY = 0; charY < 3; charY++) {
            char c = unit->getChar(charX, charY);
            if (c != ' ') frame[toIndex(unit->getX(), unit->getY(), charX, charY)] = unit->getChar(charX, charY);
        }
    }
}

void UI::displayPixel (int x, int y, char p) {
    frame[toIndex(x, y, 1, 1)] = p;
}

void UI::clear () {
    int size = sizeX * sizeY * 9;
    for(int i = 0; i < size; i++) {
        frame[i] = ' ';
    }
}

void UI::showFrame () {
    cout << endl;
    for(int y = 0; y < sizeY; y++) {
        for (int charY = 0; charY < 3; charY++) {
            for(int x = 0; x < sizeX; x++) {
                for (int charX = 0; charX < 3; charX++) {
                    cout << frame[toIndex(x, y, charX, charY)];
                }
            }
            cout << endl;
        }
    }
    for(int i = 0; i < sizeX * 3; i++) cout << "-";
}

int UI::toIndex (int x, int y, int charX, int charY) const {
    return (y * 3 + charY) * sizeX * 3 + x * 3 + charX;
}


