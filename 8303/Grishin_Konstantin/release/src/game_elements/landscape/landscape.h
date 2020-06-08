#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <SFML/Graphics/Texture.hpp>
#include <string>

class Landscape
{
public:
    enum Type{
        Open,
        Closed
    };

private:
    std::string id;

    const Type type;
    const float fMoveCost;
    const float fOutDmgMod;
    const float fInDmgMod;

protected:
    Landscape(const std::string& id,
              Type type,
              float fMoveCost,
              float fOutDmgMod,
              float fInDmgMod);

public:
    const std::string& getID() const;

    Landscape::Type getType() const;
    float getMoveCost() const;
    float getOutDmgMod() const;
    float getInDmgMod() const;
};

#endif // LANDSCAPE_H
