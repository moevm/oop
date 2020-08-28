#include "loading_exception.hpp"

loadingException::loadingException (const string& msg) : strategyException("[Loading] " + msg) {

}
