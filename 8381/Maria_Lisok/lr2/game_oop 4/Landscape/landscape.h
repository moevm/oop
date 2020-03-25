#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include <iostream>
using namespace std;
class Landscape{
public:
    virtual ~Landscape()=default;
    virtual string getLandscapeType()=0;
    virtual bool canStand()=0;
};
#endif
