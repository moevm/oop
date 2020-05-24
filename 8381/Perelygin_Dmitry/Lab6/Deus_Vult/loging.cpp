#include "loging.h"

std::map <int,std::string> no_var{  {1,"Log: Base created"},
                                    {2,"Log: Arab warrior created"},
                                    {3,"Log: Crusader warrior created"},
                                    {4,"Log: Well created"},
                                    {5,"Log: Armory created"},
                                    {6,"Log: Stable created"},
                                    {7,"Log: Forge created"},
                                    {8,"Log: Unit die"},
                                    {9,"Log: Unit use Well"},
                                    {10,"Log: Unit use Forge"},
                                    {11,"Log: Unit use Armory"},
                                    {12,"Log: Unit use Stable"},};


void loging::initialization(int flag)
{
    if (flag == 1)
    {
        c_out = true;
    }
    if (flag == 2)
    {
        in_file = true;
        std::ofstream foutr;
        foutr.open("Log.txt", std::ios::trunc);
        foutr.close();
    }
}


void loging::No_varible(int identifier)
{
  if (c_out)
  {
      std::cout << no_var[identifier] << std::endl;
  }
  if (in_file)
  {
      std::ofstream foutr;
      foutr.open("Log.txt", std::ios::app);
      foutr << no_var[identifier] << std::endl;
      foutr.close();
  }
}

void loging::Move_message(int unit, int x, int y)
{
    if (c_out)
    {
        std::cout << "Log: Unit " << unit << " move at " << x << " " << y <<" position" << std::endl;
    }
    if (in_file)
    {
        std::ofstream foutr;
        foutr.open("Log.txt", std::ios::app);
        foutr << "Log: Unit " << unit << " move at " << x << " " << y <<" position" << std::endl;
        foutr.close();
    }
}

void loging::Attack_message(int attacker, int defender, int damage)
{
    if (c_out)
    {
        std::cout << "Log: Unit " << attacker << " deals " << damage << " damage for unit " << defender<< std::endl;
    }
    if (in_file)
    {
        std::ofstream foutr;
        foutr.open("Log.txt", std::ios::app);
        foutr << "Log: Unit " << attacker << " deals " << damage << " damage for unit " << defender<< std::endl;
        foutr.close();
    }
}
