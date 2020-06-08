#include <iostream>
#include <windows.h>
#ifndef UNITS
#define UNITS
#include "units.cpp"
#endif
using std::cout;
using std::endl;

class Terrain
{
    public:
    const int sizeX, sizeY;
    const int unitCap;
    char** field; // sizeX * sizeY array of landscape types
    UnitBase** unitList; // array of unit pointers, not more than unitCap
    int unitCount = 0;

    void removeUnit( UnitBase* u )
    {
        int pos = 0;
        while( unitList[pos] != u && pos++ < unitCount);
        for(;pos < unitCount; pos++)
            unitList[pos] = unitList[pos+1];
    }

    bool isOutOfBounds( int x, int y)
    {
        if( x < 0 || y < 0 || x >= sizeX || y >= sizeY) return true;
        else return false;
    };

    bool isOccupied( int x, int y)
    {
        for( int i = 0; i < unitCount; i++)
            if(x == unitList[i]->x && y == unitList[i]->y)
                return true;
        return false;
    };

    void render()
    {
        system("cls");
        for ( int y = 0; y < sizeY; y++ ){
            for ( int x = 0; x < sizeX; x++ )
            {
                bool haveUnit = false;
                for(int pos = 0; pos < unitCount; pos++)
                    if(unitList[pos]->x == x && unitList[pos]->y == y)
                    {
                        haveUnit = (unitList[pos]->x == x && unitList[pos]->y == y) ? true : haveUnit;
                        if(unitList[pos]->faction == "NEUTRAL") cout << '$'; else
                        if(unitList[pos]->name == "Headquarters") cout << '@'; else
                            cout << '*';
                    }

                if(!haveUnit)
                    cout << field[y][x];
            }
            cout << endl;
        }
    }



    Terrain( int x, int y, int UnitCap ) : sizeX(x), sizeY(y), unitCap(UnitCap)
    {
        unitList = new UnitBase * [UnitCap];

        field = new char* [ sizeY ];
        for ( int i = 0; i < sizeY; i++ )
            field[i] = new char [ sizeX ];

        for ( int y = 0; y < sizeY; y++ )
            for ( int x = 0; x < sizeX; x++ )
            {
                field[y][x] = ( x > 4 && y > 4 && x < 8 && y < 8)? 'F' : 'L'; //static map generation
            }

    };
    Terrain( const Terrain &t ) : sizeX(t.sizeX), sizeY(t.sizeY), unitCap(t.unitCap)
    {
        unitList = new UnitBase * [unitCap];

        field = new char* [ sizeY ];
        for ( int i = 0; i < sizeY; i++ )
            field[i] = new char [ sizeX ];

        for ( int y = 0; y < sizeY; y++ )
            for ( int x = 0; x < sizeX; x++ )
            {
                field[y][x] = t.field[y][x]; //static map generation
            }

    };

    ~Terrain() {
        delete[] unitList;
        for ( int i = 0; i < sizeY; i++ )
            delete[] field[i];
        delete[] field;
    };

    void addUnit( UnitBase* u )
    {
        if ( unitCount == unitCap )
            throw "Too much units!";
        unitList[unitCount++] = u;
    };
};

