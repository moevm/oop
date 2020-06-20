#ifndef _H_PLAYER_HPP
#define _H_PLAYER_HPP

#include <string>
#include <utility>

#include "mediator.hpp"
#include "base.hpp"
#include "event.hpp"


class Player: public EventEmitter {
    std::string _name;

public:
    Player(std::string name)
        :_name{std::move(name)} {}

    const std::string &name() const { return _name; }

    virtual bool takeTurn(Mediator *m, Base *b) =0;

    virtual ~Player() {}
};

#endif
