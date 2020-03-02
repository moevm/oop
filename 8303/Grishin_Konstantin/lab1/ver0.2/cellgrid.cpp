#include "cellgrid.h"

#include "cell.h"

CellGrid::CellGrid(unsigned int iWidth, unsigned int iHeight):
    iWidth(iWidth), iHeight(iHeight)
{
    cell_array = new Cell*[iWidth*iHeight];
    for(unsigned int i = 0; i < iWidth*iHeight; i++){
        cell_array[i] = new PCell;

        cell_array[i]->coords = Point2i{int(i%iWidth), int(i/iWidth)};
    }
}


CellGrid::~CellGrid(){
    for(unsigned int i = 0; i < iWidth*iHeight; i++){
        delete cell_array[i];
    }

    delete [] cell_array;
}


Cell* CellGrid::getCell(int x, int y){
    if((x < 0) || (x >= int(iWidth)) || (y < 0) || (y >= int(iHeight)))
        return nullptr;
    return cell_array[y * int(iWidth) + x];
}

