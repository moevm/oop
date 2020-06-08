#ifndef MEMENTO_H
#define MEMENTO_H

#include "gfield.h"
#include <fstream>

class Memento{
private:
    std::ofstream file;
    std::ifstream file_in;
public:
    Memento(std::string);
    Memento();
    ~Memento();
    void record(GField* );
    void display();
};
#endif // MEMENTO_H
