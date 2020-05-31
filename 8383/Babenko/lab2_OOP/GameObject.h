//
// Created by Никита Бабенко on 15/03/2020.
//

#ifndef INC_1_LAB_OBJECT_H
#define INC_1_LAB_OBJECT_H

#include "Point.h"
#include <ostream>

enum class ObjectType {
  UNIT,
  BASE,
  NEUTRAL_OBJECT,
  UNKNOWN
};

class GameObject {
  friend class GameField;

 protected:
  ObjectType objectType;
  Point objectPosition;
  bool isOnField = false;

  virtual void print(std::ostream &stream) const = 0;

 public:
  explicit GameObject(ObjectType type) : objectType(type) {}
  Point getPosition() {
    return objectPosition;
  }
  ObjectType getType() {
    return objectType;
  }

  friend std::ostream &operator<<(std::ostream &stream, const GameObject &object) {
    object.print(stream);
    return stream;
  }

};

#endif //INC_1_LAB_OBJECT_H
