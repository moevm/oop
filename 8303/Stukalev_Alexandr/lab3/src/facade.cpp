#include "facade.h"
#include "string.h"
#include "iostream"
#include "mediator.h"
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
    char command[80];
    this->field->print_field();
    cout << "input end game to end game\ninput move to move current unit\ninput status to show base status\ninput create to create unit\ninput attack to attack\ninput next to select next unit\n";//расписать
    cin >> command;
    while(strcmp(command, "end game") != 0 )
    {

        if(strcmp(command, "move")== 0)
        {         
            Command* curr_com = new MoveUnitComm(this->field);
            curr_com->execute();
            this->field->print_field();
        }
        else if(strcmp(command, "status")== 0)
        {
            Command* curr_com = new BaseStatusComm(this->field);
            curr_com->execute();
        }
        else if(strcmp(command, "create")== 0)
        {
            Command* curr_com = new CreateUnitComm(this->field);
            curr_com->execute();
            this->field->print_field();
        }
        else if(strcmp(command, "attack")== 0)
        {
            Mediator* mediator = new Mediator(this->field);
            Command* curr_com = new AttackComm(this->field,mediator);
            curr_com->execute();
            this->field->print_field();
        }
        else if(strcmp(command, "next")== 0)
        {
            Command* curr_com = new NextComm(this->field);
            curr_com->execute();
            this->field->print_field();
        }
        else if(strcmp(command, "show")== 0)
            this->field->print_field();
        else
        {
           cout << "Wrong command!\n";
        }
        cin >> command;
    }

}
