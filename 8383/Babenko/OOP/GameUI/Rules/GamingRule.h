#ifndef LAB2_OOP_GAMINGRULE_H
#define LAB2_OOP_GAMINGRULE_H

class GameInfo;

class GamingRule {
 public:
  int fieldWidth;
  int fieldHeight;
  virtual bool isGameOver(GameInfo &gameInfo)=0;
  virtual int nextUser(GameInfo &gameInfo)=0;

  GamingRule(int fieldWidth, int fieldHeight) :
      fieldWidth(fieldWidth),
      fieldHeight(fieldHeight) {}
};

#endif //LAB2_OOP_GAMINGRULE_H
