#ifndef LOGING_H
#define LOGING_H
#include <iostream>
#include <map>
#include <fstream>

class loging
{
protected:
    bool c_out = false;
    bool in_file = false;
public:
    loging()
    {

    }

    void initialization(int flag);

    void No_varible(int identifier);

    void Move_message(int unit, int x, int y);

    void Attack_message(int attacker, int defender, int damage);

};

#endif // LOGING_H
