#ifndef ENTITY_H
#define ENTITY_H

#include <exception>
#include <string>
#include <map>

#include <SFML/System/Vector2.hpp>
#include "game_elements/team.h"

class Entity
{
public:
    struct wrong_type: public std::exception
    {
    private:
        const char* msg;

    public:
        size_t code;
        wrong_type(const char* msg, size_t code = 0):
            msg(msg), code(code){}

        const char * what() const throw(){
            return msg;
        }
    };

    enum Type{
        Unit,
        Building,
        Object
    };
    
    virtual ~Entity(){} 
    virtual Entity* copy() const = 0;
    
    virtual void update(float time) = 0;
    
    virtual void setPosition(int x, int y) = 0;
    virtual const sf::Vector2i& getPosition() const = 0;
    
    virtual Type getEntityType() const = 0;
    virtual Team getTeam() const = 0;

    virtual std::string getInfo() const = 0;
    virtual const std::string& getID() const = 0;
    
    virtual bool delete_p() const = 0;
};

#endif // ENTITY_H
