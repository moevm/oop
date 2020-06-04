#ifndef LOGIC_TRANSFORM_H
#define LOGIC_TRANSFORM_H

#include "../structs/vector2.hpp"
#include "../base/includes.hpp"
#include "vector2.hpp"

// https://docs.unity3d.com/ScriptReference/Transform.html
class transform : public iserializable {
private:
    stts::vector2<int> position; // Tile x,y
    float rotation {}; // Rotation in grads (0..360)
    float scale {}; // For collision detection where 1 is the width of tile
    stts::vector2<float> offset; // Offset from center of tile position (-1..1) where 1 is the width of tile

public:
    explicit transform (const stts::vector2<int>& pos = stts::vector2<int>(), float rot = 0, float size = 1, const stts::vector2<float>& off = stts::vector2<float>());
    transform (const transform& copy);
    transform& operator= (const transform& copy);
    ~transform () override = default;
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    bool operator== (const transform& other) const;
    bool operator!= (const transform& other) const;

    const stts::vector2<int>& getPosition() const;
    const void setPosition(const stts::vector2<int>& pos);
};

transform::transform (const stts::vector2<int>& pos, float rot, float size, const stts::vector2<float>& off)
        : position(pos), rotation(rot), scale(size), offset(off) {
}

transform::transform (const transform& copy) {
    *this = copy;
}

transform& transform::operator= (const transform& copy) {
    if (this != &copy) {
        position = copy.position;
        rotation = copy.rotation;
        scale = copy.scale;
        offset = copy.offset;
    }
    return *this;
}

void transform::serialize (json& package) const {
    position.serialize(package["position"]);
    package["rotation"] = rotation;
    package["scale"] = scale;
    offset.serialize(package["offset"]);
}

void transform::deserialize (json& package) {
    position.deserialize(package["position"]);
    rotation = package["rotation"].get<float>();
    scale = package["scale"].get<float>();
    offset.deserialize(package["offset"]);
}

bool transform::operator== (const transform& other) const {
    return position == other.position;
}

bool transform::operator!= (const transform& other) const {
    return !operator==(other);
}

const stts::vector2<int> &transform::getPosition() const {
    return position;
}

const void transform::setPosition(const stts::vector2<int>& pos) {
    position = pos; //FIXME: why not working????????? no idea........
}

#endif //LOGIC_TRANSFORM_H