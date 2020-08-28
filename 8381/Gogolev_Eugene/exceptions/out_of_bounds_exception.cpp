#include "out_of_bounds_exception.hpp"

outOfBoundsException::outOfBoundsException (const string& msg) : strategyException("[OutOfBounds] " + msg) {

}
