//
//  MoveCommand.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef MoveCommand_hpp
#define MoveCommand_hpp

#include "Command.hpp"
#include "Unit.hpp"
#include "Field.hpp"
#include "ProxyLandscape.hpp"

class MoveCommand: public Command{
    
public:
    void execute(Unit * unit, Field * field, int toX, int toY) override;
};

#endif /* MoveCommand_hpp */
