//
//  Shooter.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Shooter_hpp
#define Shooter_hpp

#include <iostream>

#include "Field.hpp"
#include "Unit.hpp"

class Shooter: public Unit {

public:
    
    void hit (Field &field, int x, int y) override;
    void motion () override;
    void setName (char unitNumberInName) override;
    
};

#endif /* Shooter_hpp */
