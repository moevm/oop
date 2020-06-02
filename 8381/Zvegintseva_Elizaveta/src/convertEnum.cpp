#include "convertEnum.h"
string convertFromEnumToLand(LandscapeType type){
    if(type == FOREST)
        return "forest";
    else if(type == RIVER)
        return "river";
    else if(type == MOUNTAIN)
        return "mountain";
    else{
        return "no such type of landscape";
    }
}
string convertFromEnumToNeutral(NeutralType type){
    if(type == VISOR)
        return "Visor";
    else if(type == LAT)
        return "Lat";
    else if(type ==BOOTS)
        return "Boots";
    else if(type == ASCORBIC)
        return "Ascorbic";
    else if(type == LEONURUS)
        return "Leonurus";
    else if(type == BELLADONNA)
        return "Belladonna";
    else if(type == CYANIDE)
        return "Cyanide";
    else if(type == SWORD)
        return "Sword";
    else if(type == SICKLE)
        return "Sickle";
    else{
        return "no such type of neutral";
    }
}
string convertFromEnumToUnit(UnitsType type){
    if(type == ARCHER)
        return "archer";
    else if(type == SHAMAN)
        return "shaman";
    else if(type == KNIGTH)
        return "knigth";
    else if(type == RIDER)
        return "rider";
    else if(type == SWARDMAN)
        return "swardman";
    else if(type == ORK)
        return "ork";
    else if(type == COMPOSITEUNITS)
        return "compositeunits";
    else{
        return "no such type of unit";
    }
}
int convertFromNeutralToEnum(string type){
    if(type == "Visor")
        return 60;
    else if(type == "Lat")
        return 61;
    else if(type == "Boots")
        return 62;
    else if(type == "Ascorbic")
        return 63;
    else if(type == "Leonurus")
        return 64;
    else if(type == "Belladonna")
        return 65;
    else if(type == "Cyanide")
        return 66;
    else if(type == "Sword")
        return 67;
    else if(type == "Sickle")
        return 68;
    else{
        return 0;
    }
}
int convertFromUnitToEnum(string type){
    if(type == "archer")
        return 20;
    else if(type == "shaman")
        return 21;
    else if(type == "knigth")
        return 22;
    else if(type == "rider")
        return 23;
    else if(type == "swardman")
        return 24;
    else if(type == "ork")
        return 25;
    else if(type == "compositeunits")
        return 26;
    else{
        return 0;
    }
}
