#include "cell_grid.h"

#include "game_elements/cell.h"
#include "game_elements/entity.h"

CellGrid::CellGrid(unsigned int iWidth, unsigned int iHeight):
    iWidth(iWidth), iHeight(iHeight)
{
    cell_array = new Cell*[iWidth*iHeight+1];
    for(unsigned int i = 0; i < iWidth*iHeight; i++){
        cell_array[i] = new Cell(sf::Vector2i(int(i%iWidth), int(i/iWidth)),
                                 "landscape_plain");
    }
}


CellGrid::CellGrid(const CellGrid& other):
    iWidth(other.iWidth), iHeight(other.iHeight)
{
    cell_array = new Cell* [iWidth * iHeight];
    for(size_t i = 0; i < iWidth *iHeight; i++){
        cell_array[i] = new Cell(sf::Vector2i(int(i%iWidth), int(i/iWidth)),
                                 other.cell_array[i]->getLandscapeID());
        if(auto e = other.cell_array[i]->getEntity()){
            cell_array[i]->setEntity(e->copy());
        }
    }
}


CellGrid::CellGrid(CellGrid&& other):
    iWidth(other.iWidth), iHeight(other.iHeight)
{
    std::swap(cell_array, other.cell_array);
}


const CellGrid&
CellGrid::operator=(const CellGrid& other)
{
    if(&other != this){
        iWidth = other.iWidth;
        iHeight = other.iHeight;

        cell_array = new Cell* [iWidth * iHeight];
        for(size_t i = 0; i < iWidth *iHeight; i++){
            cell_array[i] = new Cell(sf::Vector2i(int(i%iWidth), int(i/iWidth)),
                                     other.cell_array[i]->getLandscapeID());
            if(auto e = other.cell_array[i]->getEntity()){
                cell_array[i]->setEntity(e->copy());
            }
        }
    }

    return *this;
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


Cell* CellGrid::getBeg(){
    return cell_array[0];
}


Cell* CellGrid::getNext(Cell *from){
    int index = from->getPos().x + from->getPos().y*int(iWidth);
    index++;
    if(index > int(iWidth*iHeight))
        return cell_array[0];
    if(index < 0)
        return cell_array[int(iWidth*iHeight)];
    return cell_array[index];
}


Cell* CellGrid::getPrev(Cell *from){
    int index = from->getPos().x + from->getPos().y*int(iWidth);
    index--;
    if(index > int(iWidth*iHeight))
        return cell_array[0];
    if(index < 0)
        return cell_array[int(iWidth*iHeight)];
    return cell_array[index];
}


Cell* CellGrid::getEnd(){
    return cell_array[int(iWidth)*int(iHeight)];
}
