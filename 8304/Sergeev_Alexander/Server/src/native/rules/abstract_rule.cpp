#include "abstract_rule.hpp"

void rules::abstract_rule::serialize (json& package) const {
    package[j_typed::type] = type();
}

void rules::abstract_rule::deserialize (json& package) {

}
