#ifndef _H_STDIO_PLAYER_HPP
#define _H_STDIO_PLAYER_HPP

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <fstream>

#include "point.hpp"
#include "game.hpp"
#include "object_print.hpp"

#include "event.hpp"
#include "logging.hpp"


class IostreamPlayer;

class IostreamCommand {
public:
    // -> whether to end turn
    virtual bool execute(const Game *g, IostreamPlayer *p,
                         Mediator *m, Base *b) =0;

    virtual ~IostreamCommand() {}
};

class IostreamPlayer: public Player {
    std::ostream *_os = nullptr;
    std::istream *_is = nullptr;
    bool _free_os, _free_is;

    std::map<std::string, IostreamCommand *> _cmd_tab {};

    void
    addCommand(const std::string &str,
               IostreamCommand *cmd);


public:
    IostreamPlayer(std::string name="");

    void
    setOstream(std::ostream *os) { _os = os; _free_is = true; }
    void
    setOstream(std::ostream &os) { _os = &os; _free_os = false; }

    std::ostream &
    ostream() const { return *_os; }

    void
    setIstream(std::istream *is) { _is = is; _free_is = true; }
    void
    setIstream(std::istream &is) { _is = &is; _free_is = false; }

    std::istream &
    istream() const { return *_is; }

    virtual bool
    takeTurn(const Game *g, Mediator *m, Base *b) override;

    int
    readInt();

    Unit *
    readUnitId(Base *b);

    Vec2
    readVec2();

    std::string
    readString();

    virtual void store(std::ostream &os) const override;

    virtual bool restore(std::istream &is,
                         RestorerTable *tab) override;
};

namespace iostream_commands {

    class Move: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *b) override
        {
            Unit *u = p->readUnitId(b);
            Vec2 to = p->readVec2();
            if (!u)
                return false;

            {
                std::ostringstream oss {};
                oss << "User requested moving " << u << " to " << to;
                p->emit(new events::UserActionEvent {p, oss.str()});
            }

            if (!m->moveUnitTo(u, to)) {
                p->ostream() << "Can't move unit " << u
                             << " to " << to << "\n";
                return false;
            }

            return true;
        }
    };

    class Attack: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *b) override
        {
            Unit *u = p->readUnitId(b);
            Vec2 to = p->readVec2();
            if (!u)
                return false;

            {
                std::ostringstream oss {};
                oss << "User requested that " << u << " attacks " << to;
                p->emit(new events::UserActionEvent {p, oss.str()});
            }

            if (!m->attackTo(u, to)) {
                p->ostream() << "Unit " << u
                             << " can't attack to " << to << "\n";
                return false;
            }

            return true;
        }
    };

    class Use: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *b) override
        {
            Unit *u = p->readUnitId(b);
            if (!u)
                return false;

            {
                std::ostringstream oss {};
                oss << "User requested that " << u
                    << " uses an object";
                p->emit(new events::UserActionEvent {p, oss.str()});
            }

            if (!m->useObject(u)) {
                p->ostream() << "Unit " << u
                             << " can't use any object there\n";
                return false;
            }

            return true;
        }
    };

    class DestroyBase: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *b) override
        {
            Unit *u = p->readUnitId(b);
            if (!u)
                return false;

            {
                std::ostringstream oss {};
                oss << "User requested that " << u
                    << " destroys a base";
                p->emit(new events::UserActionEvent {p, oss.str()});
            }

            if (!m->destroyBase(u)) {
                p->ostream() << "Unit " << u
                             << " cannot destroy any bases there\n";
                return false;
            }

            return true;
        }
    };

    class Create: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *b) override
        {
            std::string s = p->readString();

            {
                std::ostringstream oss {};
                oss << "User requested creation of unit " << s;
                p->emit(new events::UserActionEvent {p, oss.str()});
            }

            if (!b->canCreateUnit(s)) {
                p->ostream() << "Can't create unit of type "
                             << s << "\n";
                return false;
            }

            int id = b->createUnit(s, m);
            if (id < 0) {
                p->ostream() << "Failed to create a unit of type "
                             << s << "\n";
                return false;
            }

            p->ostream() << "New unit of type " << s
                         << ": " << id << "\n";
            return true;
        }
    };

    class FindBase: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *, Base *b) override
        {
            p->ostream() << "Base: " << b << "\n";
            return false;
        }
    };

    class ListUnits: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *, Base *b) override
        {
            p->ostream() << "Units:";
            for (auto iter = b->unitsBegin();
                 iter != b->unitsEnd();
                 ++iter) {
                p->ostream() << "- " << iter.id()
                             << ": " << iter.unit() << "\n";
            }

            p->ostream() << std::endl;
            return false;
        }
    };

    class DescribeAt: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *) override
        {
            auto pos = p->readVec2();
            auto info = m->infoAt(pos);

            p->ostream() << "At " << pos << "\n";
            p->ostream()
                << "- Landscape: " << info.landscape() << "\n";

            if (auto *b = info.base()) {
                p->ostream() << "- Base: " << b << "\n";
            }

            if (auto *u = info.unit()) {
                p->ostream() << "- Unit: " << u << "\n";
            }

            if (auto *n = info.neutralObject()) {
                p->ostream() << "- Object: " << n << "\n";
            }

            p->ostream() << std::endl;
            return false;
        }
    };

    class PrintMap: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *m, Base *) override
        {
            auto from = p->readVec2();
            auto to = p->readVec2();

            p->ostream() << "From " << from
                         << " to " << to << ":\n";

            for (int y = from.y(); y < to.y(); ++y) {
                for (int x = from.x(); x < to.x(); ++x) {
                    if (x != from.x()) {
                        p->ostream() << " ";
                    }
                    displayMapInfo(p->ostream(), m->infoAt({x, y}));
                }
                p->ostream() << "\n";
            }

            p->ostream() << std::endl;
            return false;
        }
    };

    class Skip: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *, IostreamPlayer *p,
                Mediator *, Base *) override
        {
            std::ostringstream oss {};
            oss << "User decided to skip the turn";
            p->emit(new events::UserActionEvent {p, oss.str()});

            return true;
        }
    };

    class Save: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *g, IostreamPlayer *p,
                Mediator *, Base *) override
        {
            std::string fn = p->readString();
            std::ofstream of {fn};
            if (!of) {
                p->ostream() << "Failed to open file\n";
                return false;
            }

            g->store(of);
            p->ostream() << "Save complete\n";

            std::ostringstream oss {};
            oss << "Saved current game to " << fn;
            p->emit(new events::UserActionEvent {p, oss.str()});

            return false;
        }
    };

    class Reset: public IostreamCommand {
    public:
        virtual bool
        execute(const Game *g, IostreamPlayer *p,
                Mediator *, Base *) override
        {
            std::ostringstream oss {};
            oss << "Requesting reset";
            p->emit(new events::UserActionEvent {p, oss.str()});

            g->requestReset();
            return true;
        }
    };

}

#endif
