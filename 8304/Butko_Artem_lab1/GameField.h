#include "Units.h"

struct Obj
{
public:
    char id;
    Unit* unit;
};

class GameField
{
public:
    Obj** Field;

    bool isOkPosition(int x, int y)
    {
        return !((x < 0) || (y < 0) || (x + 1 > nWidth) || (y + 1 > nHeight));
    }

    GameField(int height, int width) : nHeight(height), nWidth(width)
    {
        auto tmpField  = new Obj*[height];
        for (int i = 0; i < height; ++i)
            tmpField[i] = new Obj[width];

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                tmpField[i][j].id = '0';
                tmpField[i][j].unit = nullptr;
            }
        }
         Field = tmpField;
         maxOfUnits = nWidth * nHeight;
         unitCounter = 0;
    }

    void swap(GameField& other)
    {
        std::swap(Field, other.Field);
        std::swap(nWidth, other.nWidth);
        std::swap(nHeight, other.nHeight);
        std::swap(maxOfUnits, other.maxOfUnits);
        std::swap(unitCounter, other.unitCounter);
    }

    GameField(GameField const& other)
    {
        Field =  other.Field;
        nWidth = other.nWidth;
        nHeight = other.nHeight;
        maxOfUnits = other.maxOfUnits;
        unitCounter = other.unitCounter;
    }

    GameField& operator=(GameField const& other)
    {
        if (&other != this)
            GameField(other).swap(*this);
        return *this;
    }

    GameField& operator=(GameField&& other)
    {
        swap(other);
        return *this;
    }

    void addUnit(char key, int x, int y)
    {
        if (unitCounter + 1 > maxOfUnits)
            std::cout << "ОШИБКА : превышен лимит юнитов на поле!" << std::endl;
        else if (!isOkPosition(x, y))
            std::cout << "ОШИБКА : неверная позиция!" << std::endl;
        else if (Field[x][y].id != '0')
            std::cout << "ОШИБКА : тайл занят!" << std::endl;
        else {
            Field[x][y].id = key;
            switch (key) {
                case 'N':
                    Field[x][y].unit = new Ninja;
                    Field[x][y].unit->position.setPosition(x, y);
                    break;
                case 'S':
                    Field[x][y].unit = new Samurai;
                    Field[x][y].unit->position.setPosition(x, y);
                    break;
                case 'G':
                    Field[x][y].unit = new Gunner;
                    Field[x][y].unit->position.setPosition(x, y);
                    break;
                case 'C':
                    Field[x][y].unit = new Crossbowman;
                    Field[x][y].unit->position.setPosition(x, y);
                    break;
                case 's':
                    Field[x][y].unit = new Spirit;
                    Field[x][y].unit->position.setPosition(x, y);
                    break;
                case 'M':
                    Field[x][y].unit = new Monk;
                    Field[x][y].unit->position.setPosition(x, y);
                    break;
                default:
                    std::cout << "ОШИБКА : такого ID не существует" << std::endl;
                    break;
            }
        }
    }

    void moveUnit(int x1, int y1, int x2, int y2)
    {
        if (!isOkPosition(x1, y1) && !isOkPosition(x2, y2))
            std::cout << "ОШИБКА : неверная позиция!" << std::endl;
        else if (Field[x2][y2].id == '0')
        {

            Field[x2][y2].id = Field[x1][y1].id;
            Field[x1][y1].id = '0';
            Field[x2][y2].unit = Field[x1][y1].unit;
            Field[x1][y1].unit = nullptr;
            Field[x2][y2].unit->position.setPosition(x2, y2);
        }
        else
            std::cout << "ОШИБКА : тайл занят!" << std::endl;
    }

    void deleteUnit(int x, int y)
    {
        if (!isOkPosition(x, y))
             std::cout << "ОШИБКА : неверная позиция!" << std::endl;
        else
        {
            Field[x][y].id = '0';
            Field[x][y].unit = nullptr;
        }
    }

    void showField()
    {
        for (int i = 0; i < nHeight; ++i)
        {
            for (int j = 0; j < nWidth; ++j)
            {
                if (Field[i][j].id == '0')
                    std::cout << "[ ]";
                else
                    std::cout << "[" << Field[i][j].id << "]";
            }
            std::cout << std::endl;
        }
    }

    ~GameField()
    {
        for (int i = 0; i < nHeight; ++i)
        {
            delete Field[i]->unit;
            delete [] Field[i];
        }
        delete [] Field;
    }
private:
    int nHeight;
    int nWidth;
    int maxOfUnits;
    int unitCounter;
};