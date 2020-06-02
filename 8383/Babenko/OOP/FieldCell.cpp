#include "FieldCell.h"

FieldCell::FieldCell(Texture *newTexture) : FieldCell() {
  texture = newTexture;
}

bool FieldCell::canSetObject(GameObject *object) {
  if (isEmpty()) {
    this->gameObject = object;
    return true;
  } else {
    return false;
  }
}

bool FieldCell::canSetTexture(Texture *newTexture) {
  if (!this->texture) {
    this->texture = newTexture;
    return true;
  } else {
    return false;
  }
}

void FieldCell::eraseObject() {
  gameObject = nullptr;
}

std::ostream &operator<<(std::ostream &stream, const FieldCell &cell) {

  stream << " ";
  if (cell.texture) {
    if (cell.gameObject)
      cell.texture->print(stream, *cell.gameObject);
    else
      stream << *cell.texture << ' ';
  } else {
    if (cell.gameObject)
      stream << "|" << *cell.gameObject << "| ";
    else
      stream << "|.| ";
  }

  return stream;
}

FieldCell::FieldCell(FieldCell &&other) :
    gameObject(other.gameObject),
    texture(other.texture) {
  other.gameObject = nullptr;
}

FieldCell &FieldCell::operator=(FieldCell &&other) {
  if (&other == this) return *this;

  gameObject = other.gameObject;
  other.gameObject = nullptr;

  return *this;
}

FieldCell::FieldCell(const FieldCell &other) :
    gameObject(other.gameObject),
    texture(other.texture) {}

FieldCell &FieldCell::operator=(const FieldCell &other) {
  if (&other == this) return *this;

  gameObject = other.gameObject;
  texture = other.texture;

  return *this;
}