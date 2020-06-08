#ifndef CELLGRID_H
#define CELLGRID_H

#include <string>

class Cell;

class CellGrid
{
    unsigned int iWidth;
    unsigned int iHeight;
    Cell **cell_array;

public:
    CellGrid(unsigned int iWidth, unsigned int iHeight);
    CellGrid(const CellGrid& other);
    CellGrid(CellGrid&& other);

    const CellGrid &
    operator=(const CellGrid& other);

    ~CellGrid();
    Cell* getCell(int x, int y); // starts by (0, 0)
    void updateCell(const std::string & id, int x, int y);

    Cell* getBeg();
    Cell* getNext(Cell*);   //
    Cell* getPrev(Cell*);   // For field iterrator
    Cell* getEnd();         //
};

#endif // CELLGRID_H
