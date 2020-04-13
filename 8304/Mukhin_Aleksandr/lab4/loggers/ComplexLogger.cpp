#include <ctime>
#include "ComplexLogger.h"

bool ComplexLogger::write(std::string information) {
    time_t now = time(0);
    char* dt = ctime(&now);
    logger->write(std::string(dt) + "\t\t\t\t\t\t: " + information + '\n');
    return true;
}
