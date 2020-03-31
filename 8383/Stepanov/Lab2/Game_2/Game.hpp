//
//  Game.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>

#include "Base.hpp"
#include "Field.hpp"
#include "Landscape.hpp"
#include "ProxyLandscape.hpp"
#include "NeutralObject.hpp"



class Game {
    
    Field *field;
    Base *first;
    Base *second;
    int height, width;
    
public:
    void startGame();
    void printField();
    void printPoints ();
    bool choseUnitToMove (bool &endGame);
    
};

#endif /* Game_hpp */

