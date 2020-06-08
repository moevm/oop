//
// Created by therealyou on 06.04.2020.
//

#ifndef LAB1_BASEHANDLER_H
#define LAB1_BASEHANDLER_H
constexpr int DEFAULT_BASE_HEALTH = 10;

#include <string>
#include "Command.h"
#include "Adapter.h"

class Command;

class BaseHandler {
    BaseHandler *next;
protected:
    GameField *gameField;
public:
    explicit BaseHandler(GameField *);

    void setNext(BaseHandler *next);

    virtual void handle(std::string &command, int player, std::string &mode) {
        if (next)
            next->handle(command, player, mode);
        else {
            throw LogicException("incorrect command", command);
        }
    }
};

class SetBaseHandler : public BaseHandler {
    int numberBase;
public:
    explicit SetBaseHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class SetUnitHandler : public BaseHandler {
    int unitId;
public:
    explicit SetUnitHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};


class MoveUnitUpHandler : public BaseHandler {
public:
    explicit MoveUnitUpHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class MoveUnitDownHandler : public BaseHandler {
public:
    explicit MoveUnitDownHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class MoveUnitLeftHandler : public BaseHandler {
public:
    explicit MoveUnitLeftHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class MoveUnitRightHandler : public BaseHandler {
public:
    explicit MoveUnitRightHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class AttackUnitHandler : public BaseHandler {
public:
    explicit AttackUnitHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};


class ShowStatusHandler : public BaseHandler {
public:
    explicit ShowStatusHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class HelpHandler : public BaseHandler {
public:
    explicit HelpHandler(GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class SwitchLogHandler : public BaseHandler {
    Adapter *adapter;
public:
    explicit SwitchLogHandler(Adapter *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class TurnOnOffLog : public BaseHandler {
    Adapter *adapter;
public:
    explicit TurnOnOffLog(Adapter *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class SaveHandler : public BaseHandler {
    Adapter *adapter;
public:
    explicit SaveHandler(Adapter *, GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class LoadHandler : public BaseHandler {
    Adapter *adapter;
public:
    explicit LoadHandler(Adapter *, GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

class SetTitanHandler : public BaseHandler {
    Adapter *adapter;
public:
    explicit SetTitanHandler(Adapter *, GameField *);

    void handle(std::string &command, int player, std::string &mode) override;
};

#endif //LAB1_BASEHANDLER_H
