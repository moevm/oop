//
//  Cell.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

class Landscape;
class Unit;
class NeutralObject;


class Cell {


 public:
    
    Unit* unit = nullptr;
    Landscape* landscape = nullptr;
    NeutralObject* neutralObject = nullptr;
    char base[3] = {'\0'};
    
    int whatHere ();
    
};


#endif /* Cell_hpp */
