#ifndef LAB2_OOP_SHOWREQUEST_H
#define LAB2_OOP_SHOWREQUEST_H

#include "Request.h"

#include <memory>
#include "ShowBaseRequest.h"
#include "ShowUnitRequest.h"

class ShowRequestHandler: public RequestHandler{
 public:
  bool canHandle(std::vector<std::string> &cmd) override{
    return cmd.size() > 1 && cmd[0] == "show";
  }

  RequestPtr handle(std::vector<std::string> &cmd) override{
    if (canHandle(cmd)){
      cmd.erase(cmd.begin());

      auto firstHandler = new ShowUnitRequestHandler;
      auto secondHandler = new ShowBaseRequestHandler;
      firstHandler->setNext(secondHandler);

      return firstHandler->handle(cmd);
    }

    if (next)
      return next->handle(cmd);
    return std::make_unique<Request>();
  }
};

#endif //LAB2_OOP_SHOWREQUEST_H
