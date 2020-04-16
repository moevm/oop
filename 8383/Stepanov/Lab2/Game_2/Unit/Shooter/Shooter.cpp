//
//  Shooter.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Shooter.hpp"

void Shooter::hit (Field &field, int x, int y) {
      std::cout << "I'm shooting at you" << std::endl;
    
    if (this->x < x) {
        
        for (int i = x; i < field.getWidth(); i++) {
            Unit *u = field.getUnit(i, y);
            if (!u) continue;
            u->incHealth(-(attack.getPoint()));
        }
        
    } else if (this->x > x) {
        
        for (int i = x; i >= 0; i--) {
            Unit *u = field.getUnit(i, y);
            if (!u) continue;
            u->incHealth(-(attack.getPoint()));
        }
        
    } else if (this->y < y) {
       
        for (int i = y; i < field.getHeight(); i++) {
            Unit *u = field.getUnit(x, i);
            if (!u) continue;
            u->incHealth(-(attack.getPoint()));
        }
    } else if (this-> y > y) {
        
        for (int i = y; y >= 0; i--) {
            Unit *u = field.getUnit(x, i);
            if (!u) continue;
            u->incHealth(-(attack.getPoint()));
        }

    }
  }
  
  void Shooter::motion () {
      std::cout << "I'm going and wathching you" << std::endl;
  }

void Shooter::setName (char unitNumberInName) {
    if (unitNumberInName % 2 == 0) {
        name[0] = unitNumberInName;
        name[1] = '>';
    } else {
        name[0] = '<';
        name[1] = unitNumberInName;
    }
    name[2] = '\0';
}
