#ifndef LAB2_OOP_LOGFORMAT_H
#define LAB2_OOP_LOGFORMAT_H

#include <string>

class LogFormat {
 public:
  virtual std::string getFormatted(std::string &stringToFormat)=0;
};

#endif //LAB2_OOP_LOGFORMAT_H
