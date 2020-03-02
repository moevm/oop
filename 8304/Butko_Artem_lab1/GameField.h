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
            std::cout << "Error Add: reached limit of units" << std::endl;
        else if ((x - 1 < 0) || (y - 1 < 0) || (x > nWidth) || (y > nHeight))
            std::cout << "Error Add: wrong position" << std::endl;
        else if (Field[x - 1][y - 1].id != '0')
            std::cout << "Error Add: tale is busy" << std::endl;
        else {
            Field[x - 1][y - 1].id = key;
            switch (key) {
                case 'N':
                    Field[x - 1][y - 1].unit = new Ninja;
                    Field[x - 1][y - 1].unit->position.setPosition(x, y);
                    break;
                case 'S':
                    Field[x - 1][y - 1].unit = new Samurai;
                    Field[x - 1][y - 1].unit->position.setPosition(x, y);
                    break;
                case 'G':
                    Field[x - 1][y - 1].unit = new Gunner;
                    Field[x - 1][y - 1].unit->position.setPosition(x, y);
                    break;
                case 'C':
                    Field[x - 1][y - 1].unit = new Crossbowman;
                    Field[x - 1][y - 1].unit->position.setPosition(x, y);
                    break;
                case 's':
                    Field[x - 1][y - 1].unit = new Spirit;
                    Field[x - 1][y - 1].unit->position.setPosition(x, y);
                    break;
                case 'M':
                    Field[x - 1][y - 1].unit = new Monk;
                    Field[x - 1][y - 1].unit->position.setPosition(x, y);
                    break;
                default:
                    break;
            }
        }
    }

    void moveUnit(int x1, int y1, int x2, int y2)
    {
        if (Field[x2 - 1][y2 - 1].id == '0')
        {

            Field[x2 - 1][y2 - 1].id = Field[x1 - 1][y1 - 1].id;
            Field[x1 - 1][y1 - 1].id = '0';
            Field[x2 - 1][y2 - 1].unit = Field[x1 - 1][y1 - 1].unit;
            Field[x1 - 1][y1 - 1].unit = nullptr;
            Field[x2 - 1][y2 - 1].unit->position.setPosition(x2, y2);
        }
        else
            std::cout << "Error: this tale is busy!";
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
        /*for (int i = 0; i < nHeight; ++i)
        {
            //delete Field[i]->unit;
            delete [] Field[i];
        }
        delete [] Field;*/
    }
private:
    int nHeight;
    int nWidth;
    int maxOfUnits;
    int unitCounter;
};