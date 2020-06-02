#ifndef LAB2_OOP_LOADEDREQUESTINTERPRETER_H
#define LAB2_OOP_LOADEDREQUESTINTERPRETER_H

#include "Requests/Request.h"

#include "Requests/AttackRequest.h"
#include "Requests/CreateRequest.h"
#include "Requests/MoveRequest.h"
#include "Requests/ShowRequest.h"
#include "Requests/ExitRequest.h"
#include "Requests/NewRequest.h"

class LoadedRequestInterpreter {
 private:
  AttackRequestHandler *attackHandler;
  CreateRequestHandler *createHandler;
  MoveRequestHandler *moveHandler;
  ShowRequestHandler *showHandler;
  ExitRequestHandler *exitHandler;
  NewRequestHandler *newHandler;


 public:
  LoadedRequestInterpreter() {
    attackHandler = new AttackRequestHandler();
    createHandler = new CreateRequestHandler();
    moveHandler = new MoveRequestHandler();
    showHandler = new ShowRequestHandler();
    exitHandler = new ExitRequestHandler();
    newHandler = new NewRequestHandler();

    attackHandler->setNext(createHandler);
    createHandler->setNext(moveHandler);
    moveHandler->setNext(showHandler);
    showHandler->setNext(exitHandler);
    exitHandler->setNext(newHandler);
  }

  RequestPtr handle(std::string requestString) {
    std::vector<std::string> requestSplitted;
    std::stringstream stream(requestString);
    std::string requestWord;
    while (stream >> requestWord)
      requestSplitted.push_back(requestWord);

    return attackHandler->handle(requestSplitted);
  }

  ~LoadedRequestInterpreter() {
    delete attackHandler;
    delete createHandler;
    delete moveHandler;
    delete showHandler;
    delete exitHandler;
    delete newHandler;
  }
};

#endif //LAB2_OOP_LOADEDREQUESTINTERPRETER_H
