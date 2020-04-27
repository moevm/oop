#include "loging.h"

std::map <int,std::string> no_var{  {1,"Log: Base created"},
                                    {2,"Log: Arab warrior created"},
                                    {3,"Log: Crusader warrior created"},
                                    {4,"Log: Well created"},
                                    {5,"Log: Armory created"},
                                    {6,"Log: Stable created"},
                                    {7,"Log: Forge created"},
                                    {8,"Log: Unit die"},};


void loging::initialization(int flag)
{
    if (flag == 1)
    {
        c_out = true;
    }
    if (flag == 2)
    {
        in_file = true;
        std::ofstream fout;
        fout.open("Log.txt", std::ios::trunc);
        fout.close();
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
      std::ofstream fout;
      fout.open("Log.txt", std::ios::app);
      fout << no_var[identifier] << std::endl;
      fout.close();
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
        std::ofstream fout;
        fout.open("Log.txt", std::ios::app);
        fout << "Log: Unit " << unit << " move at " << x << " " << y <<" position" << std::endl;
        fout.close();
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
        std::ofstream fout;
        fout.open("Log.txt", std::ios::app);
        fout << "Log: Unit " << attacker << " deals " << damage << " damage for unit " << defender<< std::endl;
        fout.close();
    }
}

