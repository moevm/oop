#ifndef LAB2_OOP_SHOWUNITREQUEST_H
#define LAB2_OOP_SHOWUNITREQUEST_H

#include "Request.h"

class ShowUnitRequest : public Request {
 private:
  Point unitPosition;

 public:
  explicit ShowUnitRequest(Point p) : unitPosition(p) {}
  void execute(GameInfo &gameInfo) override {
    auto object = gameInfo.getField().getCell(unitPosition)->getObject();
    if (object && object->getType() == ObjectType::UNIT) {
      auto unit = dynamic_cast<Unit *>(object);

      game::log << "[Game] Obtained unit showcase request" << game::logend;
      std::cout << "[Game] Unit info: " << std::endl
                << "\tHP: " << unit->getUnitHealth() << std::endl
                << "\tWeapon: " << unit->getUnitWeapon() << std::endl
                << "\tArmor: " << unit->getUnitArmor() << std::endl;
    } else {
      std::cout << "Empty cell" << std::endl;
    }
  }
};

class ShowUnitRequestHandler : public RequestHandler {
 public:
  bool canHandle(std::vector<std::string> &cmd) override {
    return cmd.size() == 3 && cmd[0] == "unit";
  }

  virtual RequestPtr handle(std::vector<std::string> &cmd) override {
    if (canHandle(cmd)) {
      int x = std::stoi(cmd[1]);
      int y = std::stoi(cmd[2]);
      Point unitPosition(x, y);
      return RequestPtr(new ShowUnitRequest(unitPosition));
    }

    if (next)
      return next->handle(cmd);

    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_SHOWUNITREQUEST_H
