//
//  HitCommand.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "HitCommand.hpp"

void HitCommand::execute(Unit * unit, Field * field, int toX, int toY) {
    
         if (unit->uid != 0 && field->whatInCell(toX, toY) == 2) {   // if uid == 0 -> chosenUnit is Smoker
                                                                           // whatInCell == 2 -> in cell neutralObject
             NeutralObject *n = field->getNeutralObject(toX, toY);
             
             if (n) {
                 *n += unit;
             }
             
             
         } else {
             
             if (unit->attackIsBlocked){
                 std::cout << "Attack is blocked on this landscape" << std::endl;
                 return;
             }
             unit->hit(field, toX, toY);
         }

    
}
