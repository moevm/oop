#ifndef _H_PLAYER_HPP
#define _H_PLAYER_HPP

#include <string>
#include <utility>

#include "mediator.hpp"
#include "base.hpp"
#include "event.hpp"
#include "storable.hpp"


class Game;

class Player: public EventEmitter,
              public Storable {
    std::string _name;

public:
    explicit Player(std::string name="")
        :_name{std::move(name)} {}

    const std::string &name() const { return _name; }

    virtual bool takeTurn(const Game *g, Mediator *m, Base *b) =0;

    virtual void
    store(std::ostream &os) const
    {
        os << name() << "\n";
    }

    virtual bool
    restore(std::istream &is, RestorerTable *)
    {
        std::ws(is);
        std::getline(is, _name);
        return !is.fail();
    }

    virtual ~Player() {}
};

#endif
