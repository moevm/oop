#ifndef LOGIC_ABSTRACT_GENERATOR_HPP
#define LOGIC_ABSTRACT_GENERATOR_HPP

#include "../base/includes.hpp"
#include "../game/abstract_game.hpp"

namespace generators {
    class abstract_generator : public iserializable, public ityped {
    public:
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        virtual std::unique_ptr<game::abstract_game> generate() = 0;
    };
}

#endif //LOGIC_ABSTRACT_GENERATOR_HPP
