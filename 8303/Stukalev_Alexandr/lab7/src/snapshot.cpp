#include "snapshot.h"
#include "myexeptions.h"

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
         if(x != 10 && x != 20)
         {
            correctData = false;
            throw LogicalExceptions("LoadGameComm", std::to_string(x), "x = 10 or x = 20");
         }
         if(y != 10 && y != 20)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(y), "x = 10 or x = 20");
         }
         Field newfield(x,y);
         *(this->field) = newfield;
         char baseName;
         int xb,yb;
         int healthb;
         int countA, countH, maxCount;
         str >> baseName >> xb >> yb >> healthb >> countA >> maxCount;
         if(baseName != 'A')
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(baseName), "A");
         }
         if(xb < 0 || xb > 20)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(xb), "xb > 0 and xb <= 20");
         }
         if(yb < 0 || yb > 20)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(yb), "yb > 0 and yb <= 20");
         }
         if(healthb < 0)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(healthb), "healthb > 0");
         }
         if(countA < 0)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(countA ), "countA  > 0");
         }
         if(maxCount < 0)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(maxCount), "maxCount > 0");
         }
         if(maxCount < countA)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(maxCount < countA), "maxCount >= countA");
         }
         //std::cout << baseName << xb << yb << healthb << countA << maxCount << '\n';
         this->field->create_ABase(maxCount,healthb);
         str >> baseName >> xb >> yb >> healthb >> countH >> maxCount;
         if(baseName != 'H')
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(baseName), "A");
         }
         if(xb < 0 || xb > 20)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(xb), "xb > 0 and xb <= 20");
         }
         if(yb < 0 || yb > 20)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(yb), "yb > 0 and yb <= 20");
         }
         if(healthb < 0)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(healthb), "healthb > 0");
         }
         if(countH < 0)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(countH ), "countH  > 0");
         }
         if(maxCount < 0)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(maxCount), "maxCount > 0");
         }
         if(maxCount < countH)
         {
             correctData = false;
             throw LogicalExceptions("LoadGameComm", std::to_string(maxCount < countH), "maxCount >= countH");
         }
         //std::cout << baseName << xb << yb << healthb << countA << maxCount << '\n';
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
             if(className != 'S' && className != 'D' && className != 'P')
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(className), "S, D or P");
             }
             if(xu < 0 || xu > 20)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(xu), "xu > 0 and xu <= 20");
             }
             if(yu < 0 || yu > 20)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(yu), "yu > 0 and yu <= 20");
             }
             if(health < 0)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(health), "health > 0");
             }
             if(damage < 0)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(damage ), "damage > 0");
             }
             if(armor < 0)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(armor), "armor > 0");
             }
             std::cout <<className<<xu<<yu<<health<<damage<<armor<<'\n';
             this->field->insertAUnit(className, health, damage, armor, xu, yu);
         }
         for (int i = 0; i < countH; i++)
         {
             str  >> className >> xu >> yu >> health >> damage >> armor;
             if(className != 'S' && className != 'D' && className != 'P')
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(className), "S, D or P");
             }
             if(xu < 0 || xu > 20)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(xu), "xu > 0 and xu <= 20");
             }
             if(yu < 0 || yu > 20)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(yu), "yu > 0 and yu <= 20");
             }
             if(health < 0)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(health), "health > 0");
             }
             if(damage < 0)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(damage ), "damage > 0");
             }
             if(armor < 0)
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(armor), "armor > 0");
             }
             std::cout <<className<<xu<<yu<<health<<damage<<armor<<'\n';
             this->field->insertHUnit(className, health, damage, armor, xu, yu);
         }
         char landscape;
         /*for(int i = 0; i < x*y; i++)
         {
             str >> landscape ;
             if(landscape != 'R' && landscape != 'F' && landscape != 'M' && landscape != 'P')
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(landscape), "R, F, M or P");
             }
             this->field->create_Landscape(i%y,i/x, landscape);
         }*/
         char neutral;
         /*for(int i = 0; i < x*y; i++)
         {
             str >> neutral;
             if(neutral != 'M' && neutral != 'V' && neutral != 'W' && neutral != 'A' && neutral != 'O')
             {
                 correctData = false;
                 throw LogicalExceptions("LoadGameComm", std::to_string(neutral), "M, V, W, A or O");
             }
             this->field->create_Landscape(i%y,i/x, neutral);
         }*/
         fileload.close();
}





