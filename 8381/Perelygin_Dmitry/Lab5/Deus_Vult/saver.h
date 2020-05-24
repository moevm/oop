#ifndef SAVER_H
#define SAVER_H
#include <iostream>
#include <map>
#include <fstream>
#include "base.h"
#include "field.h"
#include "neturalobjects.h"

class Saver
{
protected:
    Base *crus_base;
    Base *arab_base;
    Field* field;
    loging* Logs;
    NeturalObjects* well;
    NeturalObjects* forge;
    NeturalObjects* armory;
    NeturalObjects* stable;



public:
    Saver(Field* field_n,loging* Log_n,NeturalObjects* well_n,NeturalObjects* forge_n, NeturalObjects* armory_n, NeturalObjects* stable_n)
    {
    field = field_n;
    Logs = Log_n;
    well = well_n;
    forge = forge_n;
    armory = armory_n;
    stable = stable_n;

    }

    void add_crus_base(Base* base);

    void add_arab_base(Base* base);

    void make_save();

    void make_load();
};

#endif // SAVER_H
