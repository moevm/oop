#include "landscape_library.h"


LandscapeLibrary::~LandscapeLibrary(){
    for(auto pair: library){
        delete pair.second;
    }
}


void LandscapeLibrary::addLandscape(Landscape *landscape){
    library[landscape->getID()] = landscape;
}


const Landscape& LandscapeLibrary::getLandscape(const std::string &id) const{
    return *(library.at(id));
}
