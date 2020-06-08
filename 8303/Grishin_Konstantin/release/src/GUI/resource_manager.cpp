#include "resource_manager.h"

#include <SFML/Graphics/Texture.hpp>


ResourceManager::~ResourceManager(){
    for(auto p: textures)
        delete p.second;
}


void ResourceManager::loadTexture(const std::string &id, const std::string &path, bool smooth){
    if(textures.count(id) != 0){
        throw wrong_id("trying to create existing ID", id);
    }

    auto texture = new sf::Texture;
    texture->loadFromFile(path);
    if(smooth)
        texture->setSmooth(1);
    textures[id] = texture;
}


const sf::Texture& ResourceManager::getTexture(const std::string &id) const{
    if(textures.count(id) == 0){
        throw unknown_resource("trying to get nonexistent ID", id);
    }
    return *(textures.at(id));
}
