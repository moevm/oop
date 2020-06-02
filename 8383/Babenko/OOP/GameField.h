#ifndef OOP_LAB1_GAMEFIELD_H
#define OOP_LAB1_GAMEFIELD_H

#include "Point.h"
#include "GameObject.h"
#include "GameFieldIterator.h"
#include "FieldCell.h"
#include "Observers/UnitObserver.h"
#include "Observers/BaseObserver.h"
#include "Strategy/VikingStrategy.h"
#include "Strategy/ArcherStrategy.h"
#include "Strategy/WizardStrategy.h"
#include "Texture/SwampTexture.h"
#include "Texture/RockTexture.h"
#include "Texture/GrassTexture.h"
#include "NeutralObject/WildAnimalsArea.h"
#include "NeutralObject/House.h"
#include "NeutralObject/HolyGrail.h"
#include "NeutralObject/Battlefield.h"
#include "NeutralObject/MageGuild.h"
#include "Base.h"
#include "NeutralObject/NeutralObject.h"
#include "Unit/Unit.h"

#include <iostream>
#include <ctime>

class GameField : public BaseObserver, public UnitObserver {
 private:
  FieldCell **field;
  int fieldHeight;
  int fieldWidth;
  Texture *getRandomTexture();
  NeutralObject* getRandomNeutralObject();

 public:
  GameField();
  explicit GameField(int fieldSize);
  GameField(int fieldHeight, int fieldWidth);
  ~GameField();
  void reset();

  void deleteObject(int x, int y);
  void deleteObject(const Point &point);
  void deleteObject(GameObject *object);

  bool addObject(GameObject *object, int x, int y);
  bool addObject(GameObject *object, Point p);

  void moveObject(const Point &p1, const Point &p2);
  void moveObject(GameObject *object, const Point &p2);

  int getHeight() const;
  int getWidth() const;
  FieldCell *getCell(const Point &p) const;

  friend std::ostream &operator<<(std::ostream &stream, const GameField &field);

  GameFieldIterator begin() { return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
  GameFieldIterator end() { return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

  void onUnitAttack(Unit *unit, Unit *other) override;
  void onUnitMoved(Unit *unit, Point p) override;
  void onUnitDestroyed(Unit *unit) override;
  void onUnitDamaged(Unit *unit) override {}
  void onUnitHealed(Unit *unit) override {}

  void onBaseNewUnitCreated(Unit *unit, Point position) override;

  bool addBase(Base *base, Point position);
  bool addBase(Base *base, int x, int y);

  bool isOnField(const Point &p) const;
};

#endif //OOP_LAB1_GAMEFIELD_H