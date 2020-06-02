#ifndef LAB2_OOP_TAGFORMAT_H
#define LAB2_OOP_TAGFORMAT_H

#include <utility>

#include "LogFormat.h"

class TagFormat : public LogFormat {
 private:
  std::string tag;

 public:
  explicit TagFormat(std::string tag) : tag(std::move(tag)) {}

  std::string getFormatted(std::string &stringToFormat) override {
    return "[" + tag + "] " + stringToFormat;
  }
};

#endif //LAB2_OOP_TAGFORMAT_H
