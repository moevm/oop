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
    public:
        struct Context {
            GameMap *map;
            BaseUnit *focus;
        };

    private:
        std::list<Context> _maps {};
        bool _stop_running = false;

        static void skip_to_eol(std::istream &is);

    protected:
        virtual void
        spin(std::istream &is, std::ostream &os);

    public:
        Session() {}

        virtual const CommandFactory *
        findCommandFactory(std::string name) const =0;

        std::list<Context> &stack() { return _maps; };
        Context &context()
        {
            assert(!_maps.empty());
            return _maps.front();
        }
        GameMap *map() const
        {
            return _maps.empty() ? nullptr : _maps.front().map;
        }
        BaseUnit *focus() const
        {
            return _maps.empty() ? nullptr : _maps.front().focus;
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
