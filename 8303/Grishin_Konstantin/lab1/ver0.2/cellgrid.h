#ifndef CELLGRID_H
#define CELLGRID_H

class Cell;

class CellGrid
{
    unsigned int iWidth;
    unsigned int iHeight;
    Cell **cell_array;

public:
    CellGrid(unsigned int iWidth, unsigned int iHeight);
    ~CellGrid();
    Cell* getCell(int x, int y); // starts by (0, 0)
};

#endif // CELLGRID_H
