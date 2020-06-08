#include "printer.h"

#include <iostream>
#include "logger.h"

void Printer::init(){
    timer_s = 0;
}


Printer::Printer(Logger &logger):
    logger(logger), os(std::cout), file(0)
{}


Printer::Printer(Logger &logger, std::ofstream& ofs):
    logger(logger),
    os((ofs.is_open())?ofs:std::cout),
    file(1)
{
    if(!ofs.is_open())
        file = 0;
}


Printer::~Printer()
{
    os << logger;
}


void Printer::update(float time_ms)
{
    timer_s += time_ms/1000.f;
}


void Printer::print()
{
    if(!logger.empty()){
        if(!file){
            os << logger;
        }
        else{
            if(timer_s >= 30){
                os << logger;
                timer_s = 0;
            }
        }
    }
}
