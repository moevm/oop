#include "snapshot.h"

void Snapshot::saveGame()
{
    ofstream filesave;
    filesave.open("SaveGame.txt");
    std::ostringstream str("");
    str << field->getX() << " " << field->getY() << " "
        << alienbase->getBaseName()[0] << " " << alienbase->getX() << " " << alienbase->getY() << " "
        << alienbase->getHealth() << " " << alienbase->getCurrUnits() << " " << alienbase->getMaxUnits() << " "
        << humanbase->getBaseName()[0] << " " << humanbase->getX() << " " << humanbase->getY() << " "
        << humanbase->getHealth() << " " << humanbase->getCurrUnits() << " " << humanbase->getMaxUnits() << " ";
    //std :: cout << str.str();
    filesave << str.str();
    std::ostringstream landscape("");
    std::ostringstream neutral("");
    std::ostringstream abaseunits("");
    std::ostringstream hbaseunits("");
    std::ostringstream end("!");
    Unit* unit = nullptr;
    for (int j = 0; j < field->getY(); j++)
    {
        for(int i = 0; i < field->getX(); i++)
        {
            landscape << field->getLandscapeName(i,j);
            //neutral << field->getNeutralName(i,j);
            if(field->checkUnit(i,j))
            {
                unit = field->getUnit(i,j);
                if(unit->getArmy() == 'A')
                {
                    abaseunits << unit->getName() << " " << unit->getX() << " " << unit->getY() << " "
                               << unit->getHealth() << " " << unit->getDamage() << " " << unit->getArmor() << " ";
                }
                else if(unit->getArmy() == 'H')
                {
                    hbaseunits << unit->getName() << " " << unit->getX() << " " << unit->getY() << " "
                               << unit->getHealth() << " " << unit->getDamage() << " " << unit->getArmor() << " ";
                }
            }
        }
        //landscape << " ";
        //neutral << " ";
    }
    filesave << abaseunits.str();
    filesave << hbaseunits.str();
    filesave << landscape.str();
    filesave << neutral.str();
    filesave << end.str();
    filesave.close();

}

void Snapshot::loadGame()
{
    ifstream fileload;
    fileload.open("SaveGame.txt");
     std::stringstream str;
     std::string s = "";
     getline(fileload, s, '!');
     str << s;
     int x, y;
     str >> x >> y;
     Field newfield(x,y);
     *(this->field) = newfield;
     char baseName;
     int xb,yb;
     int healthb;
     int countA, countH, maxCount;
     str >> baseName >> xb >> yb >> healthb >> countA >> maxCount;
     std::cout << baseName << xb << yb << healthb << countA << maxCount << '\n';
     this->field->create_ABase(maxCount,healthb);
     str >> baseName >> xb >> yb >> healthb >> countH >> maxCount;
     std::cout << baseName << xb << yb << healthb << countA << maxCount << '\n';
     this->field->create_HBase(maxCount,healthb);
     char className;
     int xu,yu;
     int health;
     int damage;
     int armor;
     //std::cout << maxCount;
     for (int i = 0; i < countA; i++)
     {
         str  >> className >> xu >> yu >> health >> damage >> armor;
         std::cout <<className<<xu<<yu<<health<<damage<<armor<<'\n';
         this->field->insertAUnit(className, health, damage, armor, xu, yu);
     }
     for (int i = 0; i < countH; i++)
     {
         str  >> className >> xu >> yu >> health >> damage >> armor;
         std::cout <<className<<xu<<yu<<health<<damage<<armor<<'\n';
         this->field->insertHUnit(className, health, damage, armor, xu, yu);
     }
     char landscape;
     /*for(int i = 0; i < x*y; i++)
     {
         str >> landscape ;
         this->field->create_Landscape(i%y,i/x, landscape);
     }*/
     char neutral;
     /*for(int i = 0; i < x*y; i++)
     {
         str >> neutral;
         this->field->create_Landscape(i%y,i/x, neutral);
     }*/
     fileload.close();
}





