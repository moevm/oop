#ifndef TREE_H
#define TREE_H


#include "game_elements/neutral_objects/object.h"

class Tree : public Object
{
    inline static const std::string id = "object_tree";
    sf::Vector2i pos;
    int durability;

    void setPosition(int x, int y) override;

public:
    Tree(const sf::Vector2i& pos);
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

#endif // TREE_H
