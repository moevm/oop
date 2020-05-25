#include "field.h"
#include <fstream>
#include "baseexception.h"
#include <exception>

    Field::Field(int size, unsigned int maximum_count)
    {
        int roll;
        plains = new Plain();
        mountains = new Mountian();
        forests = new Forest();
        srand(time(0));
        this->size=size;
        field = new class Unit**[size];
        for (int i= 0 ;i<size;i++)
        {
            field[i] = new class Unit*[size];
        }

        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                field[i][j]= nullptr;
            }
        }
        unit_count = 0;
        max_count = maximum_count;
        landscape = new Landscapes**[size];
        obj_field = new class NeturalObjects**[size];
        landscape_view = new int*[size];
        obj_view = new int*[size];
        for (int i= 0 ;i<size;i++)
        {
             landscape[i] = new Landscapes*[size];
            landscape_view[i] = new int[size];
            obj_field[i] = new class NeturalObjects*[size];
            obj_view[i] = new int[size];
        }

        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                obj_view[i][j] = 0;
                obj_field[i][j]= nullptr;
                roll = rand() % 3 + 1;
                landscape_view[i][j]= roll;
                if (roll == 1)
                landscape[i][j]=plains;
                if (roll == 2)
                landscape[i][j]=forests;
                if (roll == 3)
                landscape[i][j]=mountains;
            }
        }

       obj_field = new class NeturalObjects**[size];
        for (int i= 0 ;i<size;i++)
        {
            obj_field[i] = new class NeturalObjects*[size];
        }

        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                obj_field[i][j]= nullptr;
            }
        }


           base_field = new class Base**[size];
         for (int i= 0 ;i<size;i++)
         {
             base_field[i] = new class Base*[size];
         }

         for (int i = 0;i<size;i++)
         {
             for (int j = 0;j<size;j++)
             {
                 base_field[i][j]= nullptr;
             }
         }
    }


    Field::Field(const class Field &input_field)
    {
        max_count=input_field.max_count;
        unit_count = input_field.unit_count;
        size = input_field.size;
        field = new class Unit**[size];
        for (int i = 0;i<size;i++)
        {
            field[i] = new class Unit*[size];
        }

        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                field[i][j]= input_field.field[i][j];
            }
        }
    }

    unsigned int Field::get_max_count()
    {
        return max_count;
    }

    int Field::get_size()
    {
        return size;
    }


    class Unit*  Field::get_unit(int x, int y)
    {
        if ((x<=size) & (y<=size))
        return field[x][y];
        else return nullptr;
    }

    void Field::add_netural_obj(class NeturalObjects* net_obj, int x, int y,int num)
    {
        if ((x>get_size()-1) || (y>get_size()-1) || (x<0) || (y<0))
        {
            throw std::invalid_argument("x or y doesn't exist\n");
        }
        if (obj_field[x][y]!=nullptr)
        {
            throw std::invalid_argument("x or y doesn't exist\n");
        }
        if(obj_field[x][y]== nullptr)
        {
            obj_field[x][y]=net_obj;
            obj_view[x][y]=num;
        }
    }

    void Field::set_land(int x, int y, int type)
    {

                landscape_view[x][y]= type;
                if (type == 1)
                landscape[x][y]=plains;
                if (type == 2)
                landscape[x][y]=forests;
                if (type == 3)
                landscape[x][y]=mountains;

    }

    void Field::add_base(class Base* base, int x, int y)
    {
        if ((x>get_size()-1) || (y>get_size()-1) || (x<0) || (y<0))
        {
            throw std::invalid_argument("x or y is invalid value\n");
        }
        if(base_field[x][y]== nullptr)
        {
            base_field[x][y]=base;
        }
    }

    int Field::get_obj_type(int x, int y)
    {

        return obj_view[x][y];
    }

    NeturalObjects* Field::get_obj(int x, int y)
    {
        if ((x>get_size()-1) || (y>get_size()-1) || (x<0) || (y<0))
        {
            throw std::invalid_argument("x or y is invalid value\n");
        }
        if (obj_field[x][y]==nullptr)
        {
            throw std::invalid_argument("Net. obj. is not here\n");
        }
        return obj_field[x][y];
    }

    void Field::clear_unit()
    {
        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {

                field[i][j]= nullptr;
            }
        }
    }
    void Field::clear_obj()
    {
        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                obj_view[i][j] = 0;
                obj_field[i][j]= nullptr;
            }
        }
    }
    void  Field::set_unit_count(int value)
    {
        unit_count+=value;
    }

    void Field::show_landscape()
    {
       for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                std::cout << landscape_view[i][j] <<"   ";

            }
            std::cout << std::endl;
        }
    }

    void  Field::show_id()
    {
        //std::cout << size <<'\n';
        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                if (field[j][i]!=nullptr)
                std::cout << field[j][i]->get_name() <<"   ";
                else
                std::cout << "0" <<"   ";

            }
            std::cout << std::endl;
        }
    }

    void  Field::show_field()
    {
        //std::cout << size <<'\n';
        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                std::cout << field[j][i] <<"   ";

            }
            std::cout << std::endl;
        }
    }

    void  Field::show_net_obj()
    {
        //std::cout << size <<'\n';
        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                std::cout << obj_field[j][i] <<"   ";

            }
            std::cout << std::endl;
        }
    }

    void  Field::show_base()
    {
        //std::cout << size <<'\n';
        for (int i = 0;i<size;i++)
        {
            for (int j = 0;j<size;j++)
            {
                std::cout << base_field[j][i] <<"   ";

            }
            std::cout << std::endl;
        }
    }

    void  Field::delete_unit( int x, int y)
    {
        field[x][y]=nullptr;
        unit_count--;
        //std::cout << "delete unit" << x << y <<std::endl;
    }




    int  Field::add_unit(class Unit *unit,int x, int y, int change_pos)
    {
     if ((x>get_size()-1) || (y>get_size()-1) || (x<0) || (y<0))
     {
         throw std::invalid_argument("x or y is invalid value\n");
     }
     if ((x<=size) & (y<=size))
     {
         if ((max_count>unit_count) || (change_pos))
         {
             if (field[x][y]==nullptr)
             {
             field[x][y] = unit;
             get_landscape(x,y)->apply_debuff(unit);
             if (change_pos)
             {
             unit->set_x(x);
             unit->set_y(y);
             unit_count+=1;
             }
             return 1;
             }
             else
             std::cout << "place not empty" << std::endl;
             return 0;
          }
         else
             std::cout << "not enough unit count" << std::endl;
             return 0;
        }
     else
         std::cout << "Position is out of Field" << std::endl;
         return 0;
    }

     Field::~Field()
    {
        std::cout << "Destructor called for Field " << std::endl;
    }


     class Landscapes* Field::get_landscape(int x, int y)
     {
        return landscape[x][y];
     }

     void Field::save_land()
     {
         std::ofstream fout;
         fout.open("Save.txt", std::ios::app);
         for (int i = 0;i<size;i++)
          {
              for (int j = 0;j<size;j++)
              {
                  fout << landscape_view[i][j] <<"   ";

              }
              fout << std::endl;
          }
         fout.close();
     }

     void Field::save_obj()
     {
         std::ofstream fout;
         fout.open("Save.txt", std::ios::app);
         for (int i = 0;i<size;i++)
          {
              for (int j = 0;j<size;j++)
              {
                  fout << obj_view[i][j] <<"   ";

              }
              fout << std::endl;
          }
        fout.close();
     }
