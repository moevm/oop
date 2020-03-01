#ifndef _INTERACTIVE_HPP_
#define _INTERACTIVE_HPP_

#include <iostream>
#include <string>
#include <list>

#include "map.hpp"
#include "unit.hpp"
#include "event.hpp"


namespace interactive {

    class Session;

    class Command {
    public:
        virtual void
        run(Session *, std::ostream &) const =0;

        virtual ~Command() {}
    };

    class CommandFactory {
    public:
        virtual Command *
        create(std::istream &, std::ostream &) const =0;

        virtual ~CommandFactory() {}
    };

    class Session {
    private:
        GameMap *_map = nullptr;
        BaseUnit *_focus = nullptr;
        bool _stop_running = false;

        static void skip_to_eol(std::istream &is);

    protected:
        virtual void
        spin(std::istream &is, std::ostream &os);

    public:
        Session() {}

        virtual const CommandFactory *
        findCommandFactory(std::string name) const =0;

        GameMap *map() const
        {
            return _map;
        }
        void resetMap(GameMap *map)
        {
            if (_map)
                delete _map;
            _map = map;
            _focus = nullptr;
        }

        BaseUnit *focus() const
        {
            return _focus;
        }
        void setFocus(BaseUnit *u)
        {
            _focus = u;
        }

        void quit() { _stop_running = true; }

        void run(std::istream &is, std::ostream &os);

        virtual ~Session() {}
    };

    template<typename T>
    class SimpleCommandFactory : public CommandFactory {
    public:
        virtual Command *
        create(std::istream &, std::ostream &) const override
        {
            return new T {};
        }
    };

    class QuitCommand : public Command {
    public:
        virtual void
        run(Session *s, std::ostream &) const override
        {
            s->quit();
        }
    };

    class BasicSession : public Session {
        static SimpleCommandFactory<QuitCommand> quit_factory;

    public:
        virtual const CommandFactory *
        findCommandFactory(std::string name) const override
        {
            return (name == "quit") ? &quit_factory : nullptr;
        }
    };
}

#endif
