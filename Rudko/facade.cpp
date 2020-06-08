#include "facade.h"

void Facade::NewGame(){
    l = new log;
    l1 = new log(1);
    field = new GField(10, 10);
    field->addLabdscape();
    base = new Base(1, 1, this->field);
    base->CreatureUnit(0, 2, "scorpio");
    l1->logt("base", 3, 0, 2, "scorpio");
    base->CreatureUnit(0, 3, "mammoth");
    l1->logt("base", 3, 0, 3, "mammoth");
    base->CreatureUnit(0, 4, "frog");
    l1->logt("base", 3, 0, 4, "frog");
    base->CreatureUnit(0, 5, "kangaroo");
    l1->logt("base", 3, 0, 5, "kangaroo");
    base->CreatureUnit(0, 6, "swallow");
    l1->logt("base", 3, 0, 6, "swallow");
    base->CreatureUnit(0, 7, "hawk");
    l1->logt("base", 3, 0, 7, "hawk");
}

void Facade::Play(){
    std::cout << "Now playning" << std::endl;
    std::string answer;
    std::string name;
    int x,y;
    while(answer != "exit"){
        std::cout << "> ";
        std::cin >> answer;
        if(answer != "exit")
            if(answer != "save")
                if(answer != "display")
                    if(answer != "base")
                        std::cin >> x >> y;
        if(answer != "exit"){
            if(answer == "base"){
                l->logf(answer, 1, 0, 0, "chek");
                l->logf(answer, 3, 0, 0, "base");
                base->Condition();
            }
            else {
                if(answer == "add"){
                    l->logf(answer, 1, 0, 0, "add");
                    std::cin >> name;
                    l->logf(answer, 3, 0, 0, name);
                    l->logf(answer, 2, x, y, name);
                    base->CreatureUnit(x, y, name);
                    field->printField();
                }
                else {
                    if(answer == "save"){
                        l->logf(answer, 1, 0, 0, "save");
                        std::string p = "Save.txt";
                        s = new Memento(p);
                        s->record(field);
                        s->~Memento();
                    }
                    else {
                        if(answer == "display"){
                            l->logf(answer, 1, 0, 0, "display");
                            s = new Memento;
                            s->display();
                            s->~Memento();
                        }
                        else {
                            std::string n = field->map1[x][y]->name;
                            l->logf(answer, 2, x, y, n);
                            base->Control(x, y, answer);
                            field->printField();
                        }
                    }
                }
            }
        }
    }
    l->logf(answer, 1, 0, 0, "exit");
    l->~log();
    std::cout << "Всего хорошего!" << std::endl;
}
