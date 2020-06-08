#ifndef ROCK_H
#define ROCK_H

#include "game_elements/neutral_objects/object.h"

class Rock : public Object
{
    inline static const std::string id = "object_rock";
    sf::Vector2i pos;
    const int maxDurability;
    int durability;

    void setPosition(int x, int y) override;
    Rock(const sf::Vector2i& pos, int dura);

public:
    Rock(const sf::Vector2i& pos);
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

#endif // ROCK_H
