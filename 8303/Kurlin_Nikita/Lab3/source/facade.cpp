#include "facade.h"

Facade::Facade()
{

}

void Facade::prepareGame()
{
    int unitMax, xx, yy;

    while (true){
        cout << "Please, enter the max numb of units on game field: \n";
        cin >> unitMax;
        if (unitMax <= 0){
            cout << "Incorrect count\n";
            continue;
        }
        while (true){
            cout << "Enter size of field (x y): \n";
            cin >> xx >> yy;
            if (xx <= 2 || yy <= 2)
                cout << "Incorrect size\n";
            else
                break;
        }
        break;
    }

    this->field = new GameField(xx, yy, unitMax);

    Mediator* mediator = new Mediator(this->field);
    this->baseHandler = new BaseHandler();
    this->createBaseHandler = new CreateBaseHandler(this->field);
    this->createUnitHandler = new CreateUnitHandler(this->field, mediator);
    this->moveUnitHandler = new MoveUnitHandler(this->field);
    this->baseStatusHandler = new BaseStatusHandler(this->field);
    this->attackHandler = new AttackHandler(this->field, mediator);
    this->wrongCommandHandler = new WrongCommandHandler();
    baseHandler->add(createBaseHandler);
    baseHandler->add(createUnitHandler);
    baseHandler->add(moveUnitHandler);
    baseHandler->add(baseStatusHandler);
    baseHandler->add(attackHandler);
    baseHandler->add(wrongCommandHandler);

    startGame();
}

void Facade::startGame()
{
    while(true){
        string commandStr;
        cout << "Enter command:" << endl;
        getline(cin, commandStr);
        baseHandler->handle(commandStr);
        field->printAll();
    }
}
