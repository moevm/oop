#ifndef FIELDOBSERVER_H
#define FIELDOBSERVER_H

#include <utility>

class Field;
class Logger;

class Master
{
    Field *field;

public:
    Master(Field *field);

    std::pair<int, int> checkEntities(Logger *logger = nullptr);
};

#endif // FIELDOBSERVER_H
