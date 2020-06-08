#include "facade.h"

void Facade::NewGame(int length, int initial_quantity){
    l = new log;
    l1 = new log(1);
    field = new GField(length, length);
    field->addLabdscape();
    field->addNeutralObject("positive card");
    field->addNeutralObject("negative card");
    field->addNeutralObject("transform card");
    base = new Base(1, 1, this->field);
    if(initial_quantity == 3){
        base->CreatureUnit(0, 2, "scorpio");
        l1->logt("base", 3, 0, 2, "scorpio");
        base->CreatureUnit(0, 4, "frog");
        l1->logt("base", 3, 0, 4, "frog");
        base->CreatureUnit(0, 6, "swallow");
        l1->logt("base", 3, 0, 6, "swallow");
        Play(2);
    }
    else {
        base->CreatureUnit(0, 2, "scorpio");
        l1->logt("base", 3, 0, 2, "scorpio");
        base->CreatureUnit(0, 4, "frog");
        l1->logt("base", 3, 0, 4, "frog");
        base->CreatureUnit(0, 6, "swallow");
        l1->logt("base", 3, 0, 6, "swallow");
        base->CreatureUnit(0, 5, "kangaroo");
        l1->logt("base", 3, 0, 5, "kangaroo");
        base->CreatureUnit(0, 3, "mammoth");
        l1->logt("base", 3, 0, 3, "mammoth");
        base->CreatureUnit(0, 7, "hawk");
        l1->logt("base", 3, 0, 7, "hawk");
        Play(1);
    }
}

void Facade::Play(int num){
    std::cout << "Now playning" << std::endl;
    std::string answer;
    std::string name;
    int x,y;
    int k = 0;
    while(answer != "exit"){
        std::cout << "> ";
        std::cin >> answer;
        if(answer != "exit")
            if(answer != "save")
                if(answer != "display")
                    if(answer != "base")
                        if(answer != "new")
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
                            if(answer == "new"){
                                l->logf(answer, 1, 0, 0, "new");
                                std::cout << "Выберите вариант игры, 1 или 2" << std::endl;
                                int number;
                                std::cin >> number;
                                while(1){
                                    if(number != 1 && number != 2){
                                        std::cout << "Выберите 1 или 2" << std::endl;
                                        std::cin >> number;
                                    }
                                    else {
                                        break;
                                    }
                                }
                                if(number == 1)
                                    NewGame(10, 6);
                                if(number == 2)
                                    NewGame(7, 3);

                            }
                            else {
                                std::string n = field->map1[x][y]->name;
                                l->logf(answer, 2, x, y, n);
                                int f = base->Control(x, y, answer, num);
                                k++;
                                std::cout << "f = " << f << std::endl;
                                if(f){
                                    l->logf("Destroy", 3, 0, 0, "base");
                                    std::cout << "Вы проиграли" << std::endl;
                                    answer = "exit";
                                }
                                if(num && k > 13 && base->getHealth() > 0){
                                    l->logf("Win", 3, 0, 0, "base");
                                    std::cout << "Вы выиграли! Победа!" << std::endl;
                                    answer = "exit";
                                }

                                field->printField();
                            }
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
