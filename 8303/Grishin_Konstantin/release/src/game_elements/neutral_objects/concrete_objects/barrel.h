#ifndef BARREL_H
#define BARREL_H

#include "game_elements/neutral_objects/object.h"

class Barrel : public Object
{
private:
    inline static const std::string id = "object_barrel";
    sf::Vector2i pos;
    bool toDelete = 0;

    void setPosition(int x , int y) override;

public:
    Barrel(const sf::Vector2i &pos);
    Entity * copy() const override;

    const sf::Vector2i& getPosition() const override;

    Object * destroy() override;
    Object * treat() override;

    void setDurability(int dura) override;
    int getDurability() const override;
    int getScore() const override;

    Type getObjectType() const override;

    std::string getInfo() const override;
    const std::string& getID() const override;

    bool delete_p() const override;
};

#endif // BARREL_H
