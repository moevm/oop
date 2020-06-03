#include "saving_exception.hpp"

savingException::savingException (const string& msg) : strategyException("[Saving] " + msg) {

}
