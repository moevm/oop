//
//  Command.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

class Unit;
class Field;

class Command {

public:
  virtual void execute(Unit * unit, Field * field, int toX, int toY) = 0;
};

#endif /* Command_hpp */
