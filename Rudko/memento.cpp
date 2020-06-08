#include "memento.h"

using namespace std;

Memento::Memento(string s){
    this->file.open("Save.txt");
}

Memento::Memento(){
    this->file_in.open("Save.txt");
}

Memento::~Memento(){
    if(this->file.is_open()){
        this->file.close();
    }
    if(this->file_in.is_open()){
        this->file_in.close();
    }
}

void Memento::record(GField* field){
    if(this->file.is_open())
    {
        int n = field->getLength();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++){
                if(field->map1[i][j]->type == "base"){
                    this->file << "> Base\n" ;//<< std::endl;
                    this->file << "  Координаты:\n    " << field->map1[i][j]->x << ' ' << field->map1[i][j]->y << '\n';//<< std::endl;
                    this->file << "  HP:\n    " << field->map1[i][j]->health << '\n';//<< std::endl;
                    this->file << "-------------------------------------------\n" ;//<< std::endl;
                } else
                if(field->map1[i][j]->type == "landscape" || field->map1[i][j]->type == "neutral"){
                    continue;
                } else{
                   this->file << ">>>>>>>>>>>> " << field->map1[i][j]->type << '\n';//<< std::endl;
                   this->file << "  Координаты:" << field->map1[i][j]->x << ' ' << field->map1[i][j]->y << '\n';//<< std::endl;
                   this->file << "  Имя:       " << field->map1[i][j]->name << '\n';//<< std::endl;
                   this->file << "  Здоровие:  " << field->map1[i][j]->health << '\n';//<< std::endl;
                   this->file << "  Атака:     " << field->map1[i][j]->attack << '\n';//<< std::endl;
                   this->file << "  Защита:    " << field->map1[i][j]->armor << '\n';//<< std::endl;
                   this->file << "-------------------------------------------\n";//<< std::endl;
                }

            }
        //this->file << '!';
        //cout << this->file.tellp()<< endl;
    }
    else {
        cout << "Ошибка при открытие файла. " << endl;
    }
}

void Memento::display(){
    if(this->file_in.is_open()){
        while(!this->file_in.eof()) {
            char c;
            this->file_in.get(c);
            cout << c;
        }
        cout << endl;
    }
    else {
        cout << "Ошибка при открытие файла." << endl;
    }
}
