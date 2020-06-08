#ifndef OOP_ADAPTER_H
#define OOP_ADAPTER_H
#include "Logger.h"
#include "../GameField.h"

class Adapter: public Logger {
public:
    explicit Adapter(GameField *field) : field(field), logger(nullptr){};
    void print() final {logger->print();};
    void setLogger(Logger *logger1) {this->logger = logger1;};
    void addLog(std::string logString) final;
    void setLog(std::string logString) final;
    void setFormat(int format) final {};
    int getFormat() final {};
private:
    Logger *logger;
    GameField *field;
};
#endif //OOP_ADAPTER_H
