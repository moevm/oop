#include "Exept.h"


except::except(std::string e): std::exception(e.c_str()){
}
