#include "log.h"


log::log(){
    file.open("logs.txt", std::ios::app);
}

log::log(int flag){

}

log::~log(){
    if(this->file.is_open()){
        this->file.close();
    }
}

void log::logf(std::string str, int flag, int x, int y, std::string name){
    if(this->file.is_open()){
        std::string cur;
        time_t now = time(0);
        std::string d = ctime(&now);
        if(flag == 1){
            cur = "log ";
            cur += d;
            cur += "\tПользователь ввел команду ";
            cur += str;
            this->file << cur << '\n';
        }
        if(flag == 2){
            if(str == "add"){
                cur = "log "; cur += d;
                cur += "\tДобавлен воин ";
                cur += name;
                cur += " на ";
                this->file << cur << x << ' ' << y << '\n';
            }
            else {
                cur = "log "; cur += d; cur += "\tДвижение воина ";
                cur += name;
                cur += " (коорд. ";
                this->file << cur << x << ", " << y << ")\n";

            }
        }
        if(flag == 3){
            if(str == "base"){
                cur = "log "; cur += d;
                cur += "\tВыведено состояние базы\n";
                this->file << cur;
            }
            else {
                cur = "log "; cur += d;
                cur += "Создание воина " + name + " на базе\n";
                this->file << cur;
            }
        }
    }
    else {
        std::cout << "Ошибка открытия файла." << std::endl;
    }
}

void log::logt(std::string str, int flag, int x, int y, std::string name){
    time_t now = time(0);
    std::string d = ctime(&now);
    if(flag == 3){
        std::cout << "log NEW" << d;
        std::cout << "Создание воина " << name << " (коорд. " << x << ", " << y << ')' << std::endl;
    }
}
