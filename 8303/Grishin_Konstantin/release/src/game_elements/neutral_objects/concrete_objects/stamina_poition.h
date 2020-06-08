#ifndef STAMINAPOITION_H
#define STAMINAPOITION_H

#include "game_elements/neutral_objects/usable.h"

class StaminaPoition : public Usable
{
    inline static const std::string id = "object_stamina_poition";
    sf::Vector2i pos;
    bool toDelete = 0;

    void setPosition(int x, int y) override;

public:
    StaminaPoition(const sf::Vector2i& pos);
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

#endif // STAMINAPOITION_H
