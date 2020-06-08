#ifndef OOP_GAMEFIELD_H
#define OOP_GAMEFIELD_H
#include "Objects/Base.h"
#define MAX_UNITS 10

class GameField {
public:
    explicit GameField(int width=20, int height=20);
    ~GameField() {};
    void setSize(int w, int h) {width = w; height = h;};
    int getWidth() { return width;};
    int getHeight() {return height;};
    void createUnit(UnitName unitName, int x, int y, Base *base);
    void deleteUnit(int x, int y, Base *base);
    void moveUnit(int x1, int y1, int x2, int y2, Base *base);
    FieldCell *getCell(int x, int y) {return &gameField[x][y];};
    void setBase(int x, int y);
    void attackUnit(int x1, int y1, int x2, int y2, Base *base, Base *enemyBase);
    void attackBase(int x1, int y1, int x2, int y2, Base *base, Base *enemyBase);
    void makeActionWithObj(int x, int y);
    std::string getLogString() {return logString;};
    int getNumUnits() { return numUnits;};
private:
    int width;
    int height;
    FieldCell **gameField;
    int numUnits;
    std::string logString;
};
#endif //OOP_GAMEFIELD_H
