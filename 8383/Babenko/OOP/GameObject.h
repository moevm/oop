//
// Created by Никита Бабенко on 15/03/2020.
//

#ifndef INC_1_LAB_OBJECT_H
#define INC_1_LAB_OBJECT_H

#include "Point.h"
#include "Logging/Log.h"
#include <ostream>
#include <unordered_map>

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

  static inline std::string getRawObjectType(const ObjectType &type) {
    switch (type) {
      case ObjectType::UNIT:return "UNIT";
      case ObjectType::BASE:return "BASE";
      case ObjectType::NEUTRAL_OBJECT:return "NEUTRAL_OBJECT";
      case ObjectType::UNKNOWN:return "";
    }
  }

  friend std::ostream &operator<<(std::ostream &stream, const GameObject &object) {
    object.print(stream);
    return stream;
  }

  friend LogProxy& operator<<(LogProxy &logger, GameObject &obj){
    logger << "Object( x: " << obj.objectPosition.x << " y: " << obj.objectPosition.y << ")";
    return logger;
  }

};

#endif //INC_1_LAB_OBJECT_H
