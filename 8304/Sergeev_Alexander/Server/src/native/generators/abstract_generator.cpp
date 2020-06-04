#include "abstract_generator.hpp"


void generators::abstract_generator::serialize (json& package) const {
    package[j_typed::type] = type();
}

void generators::abstract_generator::deserialize (json& package) {

}
