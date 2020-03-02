//
// Created by anton on 02.03.2020.
//

#include "Field.h"
bool Field::move_unit(Unit* unit, int x, int y){
    int iwidth = static_cast<int>(lengthX);
    int iheight = static_cast<int>(lengthY);
    for (int i = 0; i < iwidth; i++)
        for (int j = 0; j < iheight; j++)
        {
            if (field[i][j].unit == unit)
            {
                if (x+i >= iwidth || y+j >= iheight || x+i < 0 || y+j < 0)
                    return false;
                if (field[x+i][y+j].is_full == true)
                    return false;
                field[x+i][y+j].unit = field[i][j].unit;
                field[x+i][y+j].is_full = true;
                field[i][j].is_full = false;
                field[i][j].unit = nullptr;
                return true;
            }
        }
}
