#include "GameField.h"
#include "Exceptions/GameFieldOutOfRangeException.h"
#include "Exceptions/ImpossibleMoveException.h"
#include "Exceptions/DoublePlacingOnFieldException.h"

GameField::GameField() :
    fieldHeight(0),
    fieldWidth(0),
    field(nullptr) {}

GameField::GameField(int fieldSize) :
    fieldHeight(fieldSize),
    fieldWidth(fieldSize) {
  srand((unsigned)time(nullptr));

  field = new FieldCell *[fieldSize];
  for (int i = 0; i < fieldSize; i++) {
    field[i] = new FieldCell[fieldSize];
  }

  for (int i = 0; i < fieldSize; i++) {
    for (int j = 0; j < fieldSize; j++) {
      field[i][j].canSetTexture(getRandomTexture());
      if (rand() % 5 == 2) {
        field[i][j].canSetObject(getRandomNeutralObject());
      }
    }
  }
}

Texture* GameField::getRandomTexture() {
  switch (rand() % 3) {
    case 0:return new RockTexture();
    case 1:return new SwampTexture();
    default:return new GrassTexture();
  }
}
NeutralObject* GameField::getRandomNeutralObject() {
  switch (rand() % 5) {
    case 0:return new Battlefield();
    case 1:return new HolyGrail();
    case 2:return new House();
    case 3:return new MageGuild();
    default:return new WildAnimalsArea();
  }
}

GameField::GameField(int fieldHeight, int fieldWidth) :
    fieldHeight(fieldHeight),
    fieldWidth(fieldWidth) {
  srand((unsigned)time(nullptr));

  field = new FieldCell *[fieldHeight];
  for (int i = 0; i < fieldHeight; i++) {
    field[i] = new FieldCell[fieldWidth];
  }

  for (int i = 0; i < fieldHeight; i++) {
    for (int j = 0; j < fieldWidth; j++) {
      field[i][j].canSetTexture(getRandomTexture());
      if (rand() % 4 == 2) {
        field[i][j].canSetObject(getRandomNeutralObject());
      }
    }
  }
}

void GameField::deleteObject(int x, int y) {
  if (y < 0 || y > fieldHeight || x < 0 || x > fieldWidth) {
    throw GameFieldOutOfRangeException(x, y);
  }
  field[y][x].eraseObject();
}

bool GameField::addObject(GameObject *object, int x, int y) {
  if (object->isOnField) {
    game::log << "[GameField] " << *object << " already on field." << game::logend;
    throw DoublePlacingOnFieldException();
  }

  bool isInBorder = x < fieldWidth && y < fieldHeight && x >= 0 && y >= 0;

  if (isInBorder && field[y][x].isEmpty()) {
    field[y][x].canSetObject(object);
    object->objectPosition = Point(x, y);
    object->isOnField = true;
  } else {
    game::log << "[GameField] Impossible to add "
              << GameObject::getRawObjectType(object->getType())
              << " to field on cell (" << x << ", " << y << ")" << game::logend;

    if (!isInBorder) {
      throw GameFieldOutOfRangeException(x, y);
    }

    if (!field[y][x].isEmpty()) {
      throw DoublePlacingOnFieldException();
    }
  }

  return true;
}

void GameField::deleteObject(GameObject *object) {
  deleteObject(object->objectPosition.x, object->objectPosition.y);
}

void GameField::moveObject(const Point &p1, const Point &p2) {
  if (isOnField(p1) && isOnField(p2) && !field[p1.y][p1.x].isEmpty() && field[p2.y][p2.x].isEmpty()) {

    field[p2.y][p2.x] = std::move(field[p1.y][p1.x]);
    field[p2.y][p2.x].getObject()->objectPosition = p2;

    field[p1.y][p1.x].eraseObject();

  } else {
    game::log << "[GameField] Impossible to move object from " << p1.x
              << " " << p1.y << " to " << p2.x << " " << p2.y << game::logend;
    throw ImpossibleMoveException();
  }
}

void GameField::moveObject(GameObject *object, const Point &p2) {
  Point p1 = object->getPosition();
  moveObject(p1, p2);
}

void GameField::deleteObject(const Point &point) {
  deleteObject(point.x, point.y);
}

int GameField::getHeight() const {
  return fieldHeight;
}

int GameField::getWidth() const {
  return fieldWidth;
}

FieldCell *GameField::getCell(const Point &p) const {
  if (p.x < fieldWidth && p.y < fieldHeight)
    return &field[p.y][p.x];
  throw GameFieldOutOfRangeException(p.x, p.y);
}

GameField::~GameField() {
  for (int i = 0; i < fieldHeight; i++) {
    delete[]field[i];
  }

  delete[]field;
}

void GameField::reset() {
  srand((unsigned)time(nullptr));

  for (int i = 0; i < fieldHeight; i++) {
    delete[]field[i];
  }

  delete[]field;

  field = new FieldCell *[fieldHeight];
  for (int i = 0; i < fieldHeight; i++) {
    field[i] = new FieldCell[fieldWidth];
  }

  for (int i = 0; i < fieldHeight; i++) {
    for (int j = 0; j < fieldWidth; j++) {
      field[i][j].canSetTexture(getRandomTexture());
    }
  }
}

std::ostream &operator<<(std::ostream &stream, const GameField &field) {
  for (int y = 0; y < field.fieldHeight; y++) {
    for (int x = 0; x < field.fieldWidth; x++) {
      stream << field.field[y][x];
    }
    stream << std::endl;
  }

  return stream;
}

void GameField::onUnitMoved(Unit *unit, Point p) {

  FieldCell *cell = getCell(p);

  if (!cell->isEmpty() && cell->getObject()->getType() == ObjectType::NEUTRAL_OBJECT) {

    NeutralObject *neutralObject = static_cast<NeutralObject *>(cell->getObject());

    switch (unit->getUnitType()) {
      case UnitType::VIKING:neutralObject->setStrategy(new VikingsStrategy());
        break;
      case UnitType::ARCHER:neutralObject->setStrategy(new ArcherStrategy());
        break;
      case UnitType::WIZARD:neutralObject->setStrategy(new WizardStrategy());
        break;
      case UnitType::UNKNOWN:break;
    }

    (*unit) << neutralObject;
    cell->eraseObject();
  }

  moveObject(unit->getPosition(), p);
}

void GameField::onUnitDestroyed(Unit *unit) {
  deleteObject(unit->getPosition());
}

bool GameField::addObject(GameObject *object, Point position) {
  return addObject(object, position.x, position.y);
}

void GameField::onBaseNewUnitCreated(Unit *unit, Point position) {
  bool isPossibleToAdd = addObject(unit, position);
  if (isPossibleToAdd)
    unit->addObserver(this);
}

bool GameField::addBase(Base *base, Point position) {
  return addBase(base, position.x, position.y);
}

bool GameField::addBase(Base *base, int x, int y) {
  bool isPossibleToAdd = addObject(base, x, y);
  if (isPossibleToAdd) {
    base->addBaseObserver(this);
  }

  return isPossibleToAdd;
}

void GameField::onUnitAttack(Unit *unit, Unit *other) {

  Texture *texture = getCell(unit->getPosition())->getTexture();
  TextureProxy textureProxy(texture);
  int resDamage = unit->getUnitWeapon().getWeaponDamage() *
      textureProxy.getDamageCoef(unit->getUnitWeapon().getWeaponType())
      - other->getUnitArmor().getDamageResistance() *
          textureProxy.getAbsorptionCoef(other->getUnitArmor().getArmorType());
  if (resDamage < 0) resDamage = 0;
  other->damage(resDamage);
}

bool GameField::isOnField(const Point &p) const {
  return p.x >= 0 && p.x < fieldWidth && p.y >= 0 && p.y < fieldHeight;

}