#include "saver.h"
#include "unit.h"
#include "loging.h"


 void Saver::make_save()
 {
     std::ofstream fout;
     fout.open("Save.txt", std::ios::trunc);
     fout.close();


     fout.open("Save.txt", std::ios::app);
      fout << -1 << std::endl ;
      fout << crus_base->get_x() << " " ;
      fout << crus_base->get_y() << std::endl ;
      fout << -2 << std::endl ;
      fout << crus_base->get_unit_now() << std::endl ;
     for (int i = 1;i < crus_base->get_unit_now()+1;i++)
     {
         fout << crus_base->get_Unit(i)->get_type() << " " ;
         fout << crus_base->get_Unit(i)->get_x() << " ";
         fout << crus_base->get_Unit(i)->get_y() << " ";
         fout << crus_base->get_Unit(i)->get_hp() << " ";
         fout << crus_base->get_Unit(i)->get_attack() << " ";
         fout << crus_base->get_Unit(i)->get_armor() << " ";
         fout << crus_base->get_Unit(i)->get_move() << std::endl;
     }
     fout << -3 << std::endl ;
     field->save_land();
     fout << -4 << std::endl ;
     field->save_obj();
     fout << -5 << std::endl ;
     fout.close();
 }

 void Saver:: add_crus_base(Base *base)
 {
     crus_base = base;
 }


 void Saver::make_load()
 {
     std::ifstream fin;
     fin.open("Save.txt", std::ios::in);
     int ind = 0,x,y;
     char t;
     while(ind!=-5)
     {
     fin >> ind;
     switch (ind) {
      case -1:
         //fin >> t;
         fin >> x >> y;
         field->add_base(crus_base,x,y);
         crus_base->set_pos(x,y);
         Logs->No_varible(1);
         //fin >> t;
         break;
      case -2:
         //fin >> t;
         int count;
         fin >> count;
         //fin >> t;
         int type,unit_id;
         for (int i=0;i<count;i++)
         {
             fin >> type;
             switch (type) {
             case 1:
                 unit_id = crus_base->createCrusaderUnit(Infantryman_ID,1, field, crus_base);
                 Logs->No_varible(3);
                 break;
             case 2:
                 unit_id = crus_base->createCrusaderUnit(Horseman_ID,1, field, crus_base);
                 Logs->No_varible(3);
                 break;
             case 3:
                 unit_id = crus_base->createCrusaderUnit(Archer_ID,1, field, crus_base);
                 Logs->No_varible(3);
                 break;
             case 4:
                 unit_id = crus_base->createArabUnit(Infantryman_ID,1, field, crus_base);
                 Logs->No_varible(2);
                 break;
             case 5:
                 unit_id = crus_base->createArabUnit(Horseman_ID,1, field, crus_base);
                 Logs->No_varible(2);
                 break;
             case 6:
                 unit_id = crus_base->createArabUnit(Archer_ID,1, field, crus_base);
                 Logs->No_varible(2);
                 break;
            }
             fin >> x >> y;
             Unit* un = crus_base->get_Unit(unit_id);
             field->add_unit(un,x,y);
             int hp = 0;
             fin >> hp;
             un->set_hp(un->get_hp()-hp);
             int attack = 0;
             fin >> attack;
             un->set_attack(attack-(un->get_attack()));
             int armor = 0;
             fin >> armor;
             un->set_armor(armor-(un->get_armor()));
             int move = 0;
             fin >> move;
             un->set_move(move-(un->get_move()));
             //fin >> t;

            }
          break;
         case -3:
         //fin >> t;
         for (int j = 0; j<field->get_size();j++)
         {
             for(int i = 0; i<field->get_size();i++)
             {
                 int l;
                 fin >> l;
                 field->set_land(j,i,l);
             }
             //fin >> t;
         }
         //fin >> t;
         break;

         case -4:
         //fin >> t;
         for (int j = 0; j<field->get_size();j++)
         {
             for(int i = 0; i<field->get_size();i++)
             {
                 int l = 0;
                 fin >> l;
                 if (l!=0)
                 if(l==1)
                 field->add_netural_obj(well,i,j,l);
                 if(l==2)
                 field->add_netural_obj(forge,i,j,l);
                 if(l==3)
                 field->add_netural_obj(armory,i,j,l);
                 if(l==4)
                 field->add_netural_obj(stable,i,j,l);
             }
             //fin >> t;
         }
         //fin >> t;
         break;
     }
     }
 }
