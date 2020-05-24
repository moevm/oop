#include "unit.h"







    int Unit::get_name()
    {
        return name;
    }

    int Unit::get_hp()
    {
        return hp;
    }

    int Unit::get_attack()
    {
        return attack;
    }

    int Unit::get_armor()
    {
        return armor;
    }

    int Unit::get_move()
    {
        return move;
    }

    int Unit::get_range()
    {
        return range;
    }

    int Unit::get_cost()
    {
        return cost;
    }

    int Unit::get_x()
    {
        return x_position;
    }

    int Unit::get_y()
    {
        return y_position;
    }
    int Unit::get_type()
    {
        return type;
    }

    void Unit::set_hp(int value)
    {
        hp=hp-value;
    }

    void Unit::set_x(int value)
    {
         x_position = value;
    }

    void Unit::set_y(int value)
    {
        y_position = value;
    }

    void Unit::set_d_range(int value)
    {
        debuff_range=value;
    }

    void Unit::set_d_attack(int value)
    {
         debuff_attack=value;
    }

    void Unit::set_d_move(int value)
    {
        debuff_move=value;
    }

    void Unit::set_attack(int value)
    {
        attack+=value;
    }

    void Unit::set_armor(int value)
    {
        armor+=value;
    }

    void Unit::set_move(int value)
    {
        move+=value;
    }


    void Unit::set_position()
    {
        for(int i= 0;i<field->get_size();i++)
        {
            for(int j= 0;j<field->get_size();j++)
            {
            if(this==field->get_unit(i,j))
                {
                    this->set_x(i);
                    this->set_y(j);
                }
            }
        }
    }

    void Unit::move_unit(int x, int y, loging* Log)
    {
        if((x<=field->get_size()) & (y<=field->get_size()))
        {
            int move = get_move() - debuff_move;
            if (move<1)
                move = 1;
            if(move>=(abs(x-x_position)+abs(y-y_position)))
            {
                if (field->add_unit(this,x,y,0)==1)
                {
                    field->set_unit_count(-1);
                    //std::cout << "unit pos" << x_position << y_position <<  std::endl;
                    field->delete_unit(x_position,y_position);
                    this->set_x(x);
                    this->set_y(y);
                    Log->Move_message(this->get_name(),x,y);
                    std::cout << "move successfully" << std::endl;
                }
                else
                 std::cout << "place is not empty" << std::endl;
            }
            else
            std::cout << "not enough move points" << std::endl;
        }

    }

    void Unit::attack_unit(class Unit** defender, loging* Log)
    {
        if (!((*defender)==nullptr))
        {
            int damage, attack, armor, range_at,attack_with_debuff = 0;
            range_at = abs(get_x() - (*defender)->get_x()) + abs(get_y() - (*defender)->get_y());
           // std::cout << range_at  << std::endl;
            int range_with_debuff = range - debuff_range;
            if (range_with_debuff<1)
                range_with_debuff=1;
            if (range >= (abs(get_x() -(*defender)->get_x()) + abs(get_y() - (*defender)->get_y())))
            {
            attack = get_attack();
            attack_with_debuff=attack - debuff_attack;
            if (attack_with_debuff<1)
                attack_with_debuff=1;
            armor = (*defender)->get_armor();
            damage = attack_with_debuff - armor;
            (*defender)->set_hp(damage);
            Log->Attack_message( get_name(), (*defender)->get_name(), damage );
            //std::cout << get_name() << " deals " <<  damage << " damage to " << (*defender)->get_name() << std::endl;

            if ((*defender)->get_hp()<1)
            {
                base->delete_unit((*defender)->get_name());
                base->minus_unit();
                field->delete_unit((*defender)->get_x(),(*defender)->get_y());
                Log->No_varible(7);
                //std::cout << "DIE DIE DYNAMITE" << std::endl;
                delete (*defender);
                (*defender = nullptr);
            }

            }
            else
            std::cout << "not enough attack range"  << std::endl;
        }
    }

   void Unit::show_debuffs()
   {
       std::cout << "attack debuff is " << debuff_attack << std::endl;
       std::cout << "range debuff is " << debuff_range << std::endl;
       std::cout << "move debuff is " << debuff_move << std::endl;
   }

   Unit::~Unit()
        {
            std::cout << "Destructor called for Unit " << name << std::endl;
        }

