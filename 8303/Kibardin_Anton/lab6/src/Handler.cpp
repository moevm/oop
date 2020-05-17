//
// Created by anton on 03.04.2020.
//

#include "Handler.h"

BaseHandler::BaseHandler(Field* ptr):next(nullptr), field(ptr) {}

SetBaseHandler::SetBaseHandler(Field* ptr):BaseHandler(ptr), numberBase(0){}

SetUnitHandler::SetUnitHandler(Field* ptr):BaseHandler(ptr){}

MoveUnitUpHandler::MoveUnitUpHandler(Field* ptr):BaseHandler(ptr){}

MoveUnitDownHandler::MoveUnitDownHandler(Field* ptr):BaseHandler(ptr){}

MoveUnitRightHandler::MoveUnitRightHandler(Field* ptr):BaseHandler(ptr){}

MoveUnitLeftHandler::MoveUnitLeftHandler(Field* ptr):BaseHandler(ptr){}

AttackUnitHandler::AttackUnitHandler(Field* ptr):BaseHandler(ptr){}

ShowStatusHandler::ShowStatusHandler(Field* ptr):BaseHandler(ptr){}

HelpHandler::HelpHandler(Field* ptr): BaseHandler(ptr){}

SwitchLogHandler::SwitchLogHandler(Adapter* adapterHandler): BaseHandler(nullptr), adapter(adapterHandler){}

TurnOnOffLog::TurnOnOffLog(Adapter* adapter1): BaseHandler(nullptr), adapter(adapter1){}

SaveHandler::SaveHandler(Adapter *adapter1, Field* ptr):BaseHandler(ptr), adapter(adapter1) {}

LoadHandler::LoadHandler(Adapter *adapter1, Field *ptr):BaseHandler(ptr), adapter(adapter1) {}

SetTitanHandler::SetTitanHandler(Adapter *adapter1, Field *ptr):BaseHandler(ptr), adapter(adapter1) {}

void BaseHandler::setNext(BaseHandler *nextCommand) {
    if(next)
        next->setNext(nextCommand);
    else
        next = nextCommand;
}

void SetBaseHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "setBase" && mode == "prepare")
    {
        //
        int x = 0, y = 0, maxObjects = 5;
        if(player == 2) {y = field->getY() - 1;x = field->getX() - 1;}
        if(player == 3) x = field->getX() - 1;
        Command* command = new SetBaseCommand(x, y, maxObjects, field, player);
        numberBase++;
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SetUnitHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "setUnit" && mode == "baseDefence")
    {
        //
        std::string unitName;
        char className;
        Base* base;
        base = field->findBase(player);
        if(!base)
        {
            std::cout << "base with this number doesn't exist" << std::endl;
            return;
        }
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        std::cout << "enter unit class[b/d/e/f/n/p]: ";
        std::cin >> className;
        Command* command = new SetUnitCommand(base, className, unitName);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void MoveUnitUpHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "moveUp")
    {
        //
        std::string unitName;
        Unit* unit;
        if(mode == "baseDefence")
        {
            std::cout << "enter unit name: ";
            std::cin >> unitName;
            unit = field->findBase(player)->findUnit(unitName);
        } else
        {
            switch (player) {
                case 1:
                    unit = field->unit1;
                    break;
                case 2:
                    unit = field->unit2;
                    break;
                case 3:
                    unit = field->unit3;
                    break;
                default:
                    break;
            }
        }
        if(!unit)
        {
            std::cout << "unit with this name doesn't exist!" << std::endl;
            return;
        }
        Command* command = new MoveUpUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SetTitanHandler::handle(std::string& commandName, int player, std::string& mode){
    if(commandName == "setTitan" && mode == "prepare")
    {
        //
        std::string unitName;
        char className;
        int x, y;
        if(player == 1)
        {
            x = 0; y = 0;
        }else if(player == 2)
        {
            x = field->getX() - 1; y = field->getY() - 1;
        } else
        {
            x = 0; y = field->getY() - 1;
        }
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        std::cout << "enter unit class[b/d/e/f/n/p]: ";
        std::cin >> className;
        Command* command = new SetUnitCommand(field, player, className, unitName, x, y);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void MoveUnitDownHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "moveDown")
    {
        //
        std::string unitName;
        Unit* unit;
        if(mode == "baseDefence")
        {
            std::cout << "enter unit name: ";
            std::cin >> unitName;
            unit = field->findBase(player)->findUnit(unitName);
        } else
        {
            switch (player) {
                case 1:
                    unit = field->unit1;
                    break;
                case 2:
                    unit = field->unit2;
                    break;
                case 3:
                    unit = field->unit3;
                    break;
                default:
                    break;
            }
        }
        Command* command = new MoveDownUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }

}

void MoveUnitLeftHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "moveLeft")
    {
        //
        std::string unitName;
        Unit* unit;
        if(mode == "baseDefence")
        {
            std::cout << "enter unit name: ";
            std::cin >> unitName;
            unit = field->findBase(player)->findUnit(unitName);
        } else
        {
            switch (player) {
                case 1:
                    unit = field->unit1;
                    break;
                case 2:
                    unit = field->unit2;
                    break;
                case 3:
                    unit = field->unit3;
                    break;
                default:
                    break;
            }
        }        Command* command = new MoveLeftUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void MoveUnitRightHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "moveRight")
    {
        //
        std::string unitName;
        Unit* unit;
        if(mode == "baseDefence")
        {
            std::cout << "enter unit name: ";
            std::cin >> unitName;
            unit = field->findBase(player)->findUnit(unitName);
        } else
        {
            switch (player) {
                case 1:
                    unit = field->unit1;
                    break;
                case 2:
                    unit = field->unit2;
                    break;
                case 3:
                    unit = field->unit3;
                    break;
                default:
                    break;
            }
        }        Command* command = new MoveRightUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void AttackUnitHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "attack")
    {
        std::string unitName;
        Unit* unit;
        int x, y;
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        unit = field->findUnit(unitName);
        if(!unit)
        {
            std::cout << "unit with this name doesn't exist!" << std::endl;
            return;
        }
        std::cout << "choose cell" << std::endl;
        std::cout << "enter x: ";
        std::cin >> x;
        std::cout << "enter y: ";
        std::cin >> y;

        if(x == unit->getX() && y == unit->getY())
        {
            std::cout << "can't attack himself!" << std::endl;
            return;
        }

        Command* command = new AttackUnitCommand(field, unit, x, y);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void ShowStatusHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "showStatus")
    {
        //
        Command* command = new ShowStatusCommand(field);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void HelpHandler::handle(std::string& commandName, int player, std::string& mode) {
    if(commandName == "help")
    {
        //
        Command* command = new HelpCommand();
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SwitchLogHandler::handle(std::string &commandName, int player, std::string& mode) {
    if(commandName == "switchLog")
    {
        std::string mode;
        std::cout << "choose stream(console/file): " << std::endl;
        std::cin >> mode;
        adapter->switchLogStream(mode);
        adapter->logChanged(mode);
    } else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void TurnOnOffLog::handle(std::string &commandName, int player, std::string& mode)
{
    if(commandName == "turnLog")
    {
        std::string mode;
        std::cout << "on/off?" << std::endl;
        std::cin >> mode;
        adapter->turnOnOffLog(mode);
    }else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SaveHandler::handle(std::string &commandName, int player, std::string& mode)
{
    if(commandName == "save")
    {
        Command* command = new SaveCommand(field);
        command->execute();
    }else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}

void LoadHandler::handle(std::string &commandName, int player, std::string& mode)
{
    if(commandName == "load")
    {
        Command* command = new LoadCommand(field);
        command->execute();
    }else
    {
        BaseHandler::handle(commandName, player, mode);
    }
}