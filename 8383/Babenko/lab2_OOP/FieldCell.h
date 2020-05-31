#ifndef LAB2_OOP_FIELDCELL_H
#define LAB2_OOP_FIELDCELL_H

#include <ostream>
#include "Texture/Texture.h"
#include "GameObject.h"

class FieldCell {
 private:
  GameObject *gameObject;
  Texture *texture;

 public:
  FieldCell() : gameObject(nullptr), texture(nullptr) {}
  FieldCell(const FieldCell &other);
  FieldCell(FieldCell &&other);
  explicit FieldCell(Texture *newTexture);

  bool isEmpty() {
    return gameObject == nullptr;
  }
  bool canSetObject(GameObject *object);
  bool canSetTexture(Texture *newTexture);
  void eraseObject();

  friend std::ostream &operator<<(std::ostream &stream, const FieldCell &cell);

  GameObject *getObject() const {
    return gameObject;
  }
  Texture *getTexture() const {
    return texture;
  }

  FieldCell &operator=(FieldCell &&other);
  FieldCell &operator=(const FieldCell &other);
};

#endif //LAB2_OOP_FIELDCELL_H
