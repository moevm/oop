#ifndef LAB2_OOP_NOFORMAT_H
#define LAB2_OOP_NOFORMAT_H

#include "LogFormat.h"

class NoFormat : public LogFormat {
  std::string getFormatted(std::string &stringToFormat) override {
    return stringToFormat;
  }
};

#endif //LAB2_OOP_NOFORMAT_H
