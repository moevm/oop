#ifndef HEALPOITION_H
#define HEALPOITION_H


#include "game_elements/neutral_objects/usable.h"


class HealingPoition : public Usable
{
    inline static const std::string id = "object_healing_poition";
    sf::Vector2i pos;
    bool toDelete = 0;

    void setPosition(int x, int y) override;

public:
    HealingPoition(const sf::Vector2i& pos);
    Entity * copy() const override;

    const sf::Vector2i& getPosition() const override;

    Object * destroy() override;
    Object * treat() override;
    Object * operator>>(class Unit* target) override;

    void setDurability(int dura) override;
    int getDurability() const override;
    int getScore() const override;

    Type getObjectType() const override;

    std::string getInfo() const override;
    const std::string& getID() const override;

    bool delete_p() const override;
};

#endif // HEALPOITION_H
