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

void BaseHandler::setNext(BaseHandler *nextCommand) {
    if(next)
        next->setNext(nextCommand);
    else
        next = nextCommand;
}

void SetBaseHandler::handle(std::string& commandName) {
    if(commandName == "setBase")
    {
        //
        int x, y, maxObjects;
        std::cout << "enter x: ";
        std::cin >> x;
        std::cout << "enter y: ";
        std::cin >> y;
        std::cout << "enter max objects: ";
        std::cin >> maxObjects;
        if(!field->checkPoint(x, y))
        {
            return;
        }
        Command* command = new SetBaseCommand(x, y, maxObjects, field, numberBase);
        numberBase++;
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName);
    }
}

void SetUnitHandler::handle(std::string& commandName) {
    if(commandName == "setUnit")
    {
        //
        std::string unitName;
        int baseNumber;
        char className;
        Base* base;
        std::cout << "enter base number: ";
        std::cin >> baseNumber;
        base = field->findBase(baseNumber);
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
        BaseHandler::handle(commandName);
    }
}

void MoveUnitUpHandler::handle(std::string& commandName) {
    if(commandName == "moveUp")
    {
        //
        std::string unitName;
        Unit* unit;
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        unit = field->findUnit(unitName);
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
        BaseHandler::handle(commandName);
    }
}

void MoveUnitDownHandler::handle(std::string& commandName) {
    if(commandName == "moveDown")
    {
        //
        std::string unitName;
        Unit* unit;
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        unit = field->findUnit(unitName);
        if(!unit)
        {
            std::cout << "unit with this name doesn't exist!" << std::endl;
            return;
        }
        Command* command = new MoveDownUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName);
    }

}

void MoveUnitLeftHandler::handle(std::string& commandName) {
    if(commandName == "moveLeft")
    {
        //
        std::string unitName;
        Unit* unit;
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        unit = field->findUnit(unitName);
        if(!unit)
        {
            std::cout << "unit with this name doesn't exist!" << std::endl;
            return;
        }
        Command* command = new MoveLeftUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName);
    }
}

void MoveUnitRightHandler::handle(std::string& commandName) {
    if(commandName == "moveRight")
    {
        //
        std::string unitName;
        Unit* unit;
        std::cout << "enter unit name: ";
        std::cin >> unitName;
        unit = field->findUnit(unitName);
        if(!unit)
        {
            std::cout << "unit with this name doesn't exist!" << std::endl;
            return;
        }
        Command* command = new MoveRightUnitCommand(field, unit);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName);
    }
}

void AttackUnitHandler::handle(std::string& commandName) {
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
        BaseHandler::handle(commandName);
    }
}

void ShowStatusHandler::handle(std::string& commandName) {
    if(commandName == "showStatus")
    {
        //
        Command* command = new ShowStatusCommand(field);
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName);
    }
}

void HelpHandler::handle(std::string& commandName) {
    if(commandName == "help")
    {
        //
        Command* command = new HelpCommand();
        command->execute();
        field->print();

    } else
    {
        BaseHandler::handle(commandName);
    }
}

void SwitchLogHandler::handle(std::string &commandName) {
    if(commandName == "switchLog")
    {
        std::string mode;
        std::cout << "choose stream(console/file): " << std::endl;
        std::cin >> mode;
        adapter->switchLogStream(mode);
        adapter->logChanged(mode);
    } else
    {
        BaseHandler::handle(commandName);
    }
}

void TurnOnOffLog::handle(std::string &commandName)
{
    if(commandName == "turnLog")
    {
        std::string mode;
        std::cout << "on/off?" << std::endl;
        std::cin >> mode;
        adapter->turnOnOffLog(mode);
    }else
    {
        BaseHandler::handle(commandName);
    }
}

void SaveHandler::handle(std::string &commandName)
{
    if(commandName == "save")
    {
        Command* command = new SaveCommand(field);
        command->execute();
    }else
    {
        BaseHandler::handle(commandName);
    }
}

void LoadHandler::handle(std::string &commandName)
{
    if(commandName == "load")
    {
        Command* command = new LoadCommand(field);
        command->execute();
    }else
    {
        BaseHandler::handle(commandName);
    }
}