//
// Created by therealyou on 06.04.2020.
//

#include <cassert>
#include "BaseHandler.h"

BaseHandler::BaseHandler(GameField *gameField) : next(nullptr), gameField(gameField) {}

SetBaseHandler::SetBaseHandler(GameField *gameField) : BaseHandler(gameField), numberBase(1) {}

SetUnitHandler::SetUnitHandler(GameField *gameField) : BaseHandler(gameField), unitId(0) {}

MoveUnitUpHandler::MoveUnitUpHandler(GameField *gameField) : BaseHandler(gameField) {}

MoveUnitDownHandler::MoveUnitDownHandler(GameField *gameField) : BaseHandler(gameField) {}

MoveUnitRightHandler::MoveUnitRightHandler(GameField *gameField) : BaseHandler(gameField) {}

MoveUnitLeftHandler::MoveUnitLeftHandler(GameField *gameField) : BaseHandler(gameField) {}

AttackUnitHandler::AttackUnitHandler(GameField *gameField) : BaseHandler(gameField) {}

ShowStatusHandler::ShowStatusHandler(GameField *gameField) : BaseHandler(gameField) {}

HelpHandler::HelpHandler(GameField *gameField) : BaseHandler(gameField) {}

SwitchLogHandler::SwitchLogHandler(Adapter *adapterHandler) : BaseHandler(nullptr), adapter(adapterHandler) {}

TurnOnOffLog::TurnOnOffLog(Adapter *adapter) : BaseHandler(nullptr), adapter(adapter) {}

SaveHandler::SaveHandler(Adapter *adapter, GameField *gameField) : BaseHandler(gameField), adapter(adapter) {}

LoadHandler::LoadHandler(Adapter *adapter, GameField *gameField) : BaseHandler(gameField), adapter(adapter) {}

SetTitanHandler::SetTitanHandler(Adapter *adapter, GameField *gameField) : BaseHandler(gameField), adapter(adapter) {}

void BaseHandler::setNext(BaseHandler *nextCommand) {
    if (next)
        next->setNext(nextCommand);
    else
        next = nextCommand;
}

void SetBaseHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "setBase" && mode == "prepare") {
        //
        int x = 0, y = 0, maxObjects = 5;
        if (player == 2) {
            y = gameField->getHeight() - 1;
            x = gameField->getWidth() - 1;
        }
        if (player == 3) x = gameField->getWidth() - 1;
        Command *command = new SetBaseCommand(x, y, maxObjects, gameField, player, DEFAULT_BASE_HEALTH);
        numberBase++;
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SetUnitHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "setUnit" && mode == "baseDefence") {
        //
        char className;
        int x, y;
        Base *base;
        base = gameField->findBase(player);
        if (!base) {
            std::cout << "base with this number doesn't exist" << std::endl;
            return;
        }
        std::cout << "enter unit class[e -- g -- p -- s -- t -- w]: ";
        std::cin >> className;
        std::cout << "enter x: ";
        std::cin >> x;
        std::cout << "enter y: ";
        std::cin >> y;
        UnitsType unitType;
        switch (className) {
            case 'e':
                unitType = UnitsType::ELF;
                break;
            case 'g':
                unitType = UnitsType::GOBLIN;
                break;
            case 'p':
                unitType = UnitsType::PEON;
                break;
            case 's':
                unitType = UnitsType::SHOOTER;
                break;
            case 't':
                unitType = UnitsType::TROLL;
                break;
            case 'w':
                unitType = UnitsType::WITCH;
                break;
            default:
                std::cerr << "\t\tUnknown type of unit" << std::endl;
        }
        Command *command = new SetUnitCommand(base, unitType, x, y, unitId);
        unitId++;
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SetTitanHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "setTitan" && mode == "prepare") {
        //
        std::string unitName;
        char className;
        int x, y;
        if (player == 1) {
            x = 0;
            y = 0;
        } else if (player == 2) {
            x = gameField->getWidth() - 1;
            y = gameField->getHeight() - 1;
        } else {
            x = 0;
            y = gameField->getHeight() - 1;
        }
        std::cout << "enter unit class[e -- g -- p -- s -- t -- w]: ";
        std::cin >> className;
        std::cout << "enter x: ";
        std::cin >> x;
        std::cout << "enter y: ";
        std::cin >> y;
        Command *command = new SetUnitCommand(gameField, className, x, y, player);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void MoveUnitUpHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "moveUp") {
        //
        int unitId;
        Unit *unit;
        if (mode == "baseDefence") {
            std::cout << "enter unit id: ";
            std::cin >> unitId;
            unit = gameField->findBase(player)->findUnit(unitId);
        } else {
            switch (player) {
                case 1:
                    unit = gameField->unit1;
                    break;
                case 2:
                    unit = gameField->unit2;
                    break;
                case 3:
                    unit = gameField->unit3;
                    break;
                default:
                    break;
            }
        }
        if (!unit) {
            std::cout << "unit with this id doesn't exist!" << std::endl;
            throw LogicException("cannot get unit with id", unitId);
        }
        Command *command = new MoveUpUnitCommand(gameField, unit);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void MoveUnitDownHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "moveDown") {
        //
        int unitId;
        Unit *unit;
        if (mode == "baseDefence") {
            std::cout << "enter unit id: ";
            std::cin >> unitId;
            unit = gameField->findBase(player)->findUnit(unitId);
        } else {
            switch (player) {
                case 1:
                    unit = gameField->unit1;
                    break;
                case 2:
                    unit = gameField->unit2;
                    break;
                case 3:
                    unit = gameField->unit3;
                    break;
                default:
                    break;
            }
        }
        if (!unit) {
            std::cout << "unit with this id doesn't exist!" << std::endl;
            throw LogicException("cannot get unit with id", unitId);
        }
        Command *command = new MoveDownUnitCommand(gameField, unit);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }

}

void MoveUnitLeftHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "moveLeft") {
        //
        int unitId;
        Unit *unit = nullptr;
        if (mode == "baseDefence") {
            std::cout << "enter unit id: ";
            std::cin >> unitId;
            unit = gameField->findBase(player)->findUnit(unitId);
        } else {
            switch (player) {
                case 1:
                    unit = gameField->unit1;
                    break;
                case 2:
                    unit = gameField->unit2;
                    break;
                case 3:
                    unit = gameField->unit3;
                    break;
                default:
                    break;
            }
        }
        if (!unit) {
            std::cout << "unit with this id doesn't exist!" << std::endl;
            throw LogicException("cannot get unit with id", unitId);
        }
        Command *command = new MoveLeftUnitCommand(gameField, unit);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void MoveUnitRightHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "moveRight") {
        //
        int unitId;
        Unit *unit;
        if (mode == "baseDefence") {
            std::cout << "enter unit id: ";
            std::cin >> unitId;
            unit = gameField->findBase(player)->findUnit(unitId);
        } else {
            switch (player) {
                case 1:
                    unit = gameField->unit1;
                    break;
                case 2:
                    unit = gameField->unit2;
                    break;
                case 3:
                    unit = gameField->unit3;
                    break;
                default:
                    break;
            }
        }
        if (!unit) {
            std::cout << "unit with this id doesn't exist!" << std::endl;
            throw LogicException("cannot get unit with id", unitId);
        }
        Command *command = new MoveRightUnitCommand(gameField, unit);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void AttackUnitHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "attack") {
        int unitId;
        Unit *unit;
        int x, y;
        if (mode == "baseDefence") {
            std::cout << "enter unit id: ";
            std::cin >> unitId;
            unit = gameField->findBase(player)->findUnit(unitId);
        } else {
            switch (player) {
                case 1:
                    unit = gameField->unit1;
                    break;
                case 2:
                    unit = gameField->unit2;
                    break;
                case 3:
                    unit = gameField->unit3;
                    break;
                default:
                    break;
            }
        }
        if (!unit) {
            std::cout << "unit with this id doesn't exist!" << std::endl;
            throw LogicException("cannot get unit with id", unitId);
        }
        std::cout << *unit;
        std::cout << "choose cell" << std::endl;
        std::cout << "enter x: ";
        std::cin >> x;
        std::cout << "enter y: ";
        std::cin >> y;

        if (x == unit->getX() && y == unit->getY()) {
            throw LogicException("Unit can't attack him self. unit id: ", unit->getId());
        }

        Command *command = new AttackUnitCommand(gameField, unit, x, y);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void ShowStatusHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "showStatus") {
        //
        Command *command = new ShowStatusCommand(gameField);
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void HelpHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "help") {
        //
        Command *command = new HelpCommand();
        command->execute();
        gameField->printField();

    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SwitchLogHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "switchLog") {
        std::string mode;
        std::cout << "choose stream(console/file): " << std::endl;
        std::cin >> mode;
        adapter->switchLogStream(mode);
        adapter->logChanged(mode);
    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void TurnOnOffLog::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "turnLog") {
        std::string mode;
        std::cout << "on/off?" << std::endl;
        std::cin >> mode;
        adapter->turnOnOffLog(mode);
    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void SaveHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "save") {
        Command *command = new SaveCommand(gameField);
        command->execute();
    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}

void LoadHandler::handle(std::string &commandName, int player, std::string &mode) {
    if (commandName == "load") {
        Command *command = new LoadCommand(gameField);
        command->execute();
    } else {
        BaseHandler::handle(commandName, player, mode);
    }
}