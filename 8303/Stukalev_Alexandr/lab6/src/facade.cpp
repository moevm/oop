#include "facade.h"
#include <string>
#include "iostream"
#include "mediator.h"

bool LoggingProxy::isLogging = 0;
bool LoggingProxy::logInFile = false;
bool LoggingProxy::logInConsole = false;
bool Logging::fileOpen = 0;
File* Logging::file = nullptr;
Facade::Facade()
{
    this->field = new Field(10, 10);
}

void Facade::start()
{
    while(!field->checkAleinBase() || !field->checkHumanBase())
    {
        Command* createbases = new CreateBaseComm(this->field);
        createbases->execute();
    }
    this->field->create_Landscape();
    this->field->show_Landscape();
    //this->field->create_Neutral(1,1,'M');
    //this->field->create_Neutral(1,2,'V');
    //this->field->create_Neutral(1,3,'W');
    //this->field->create_Neutral(1,4,'A');
    this->field->show_Neutral();
    this->field->print_field();
    //cout << "input end game to end game\ninput move to move current unit\ninput status to show base status\ninput create to create unit\ninput attack to attack\ninput next to select next unit\n";//расписать

    snapshot = new Snapshot(this->field);
    this->chainOfRespons = new ChainOfRespons();

    this->elemUnitCreate = new ElemUnitCreat(field);
    this->chainOfRespons->addToChain(elemUnitCreate);

    this->elemUnitMove = new ElemUnitMove(field);
    this->chainOfRespons->addToChain(elemUnitMove);

    this->elemUnitAttack = new ElemUnitAttack(field);
    this->chainOfRespons->addToChain(elemUnitAttack);

    this->elemBaseStatus = new ElemBaseStatus(field);
    this->chainOfRespons->addToChain(elemBaseStatus);

    this->elemNextComm = new ElemNextComm(field);
    this->chainOfRespons->addToChain(elemNextComm);

    this->elemLogging = new ElemLogging(field);
    this->chainOfRespons->addToChain(elemLogging);

    this->elemLoadComm = new ElemLoadComm(field);
    this->chainOfRespons->addToChain(elemLoadComm);

    this->elemSaveComm = new ElemSaveComm(field);
    this->chainOfRespons->addToChain(elemSaveComm);

    this->elemWrongComm = new ElemWrongComm();
    this->chainOfRespons->addToChain(elemWrongComm);

    string command;

    while(true)
    {
        cout << "Enter command:\n";
        cin >> command;
        if(command == "end")
            break;
        //chainOfRespons->chain(command);
    }

    LoggingProxy::logOff();


}
