#ifndef _DEMO_HPP_
#define _DEMO_HPP_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <typeinfo>
#include <typeindex>

#include <ctype.h>

#include "interactive.hpp"
#include "game.hpp"
#include "unit_types.hpp"
#include "event.hpp"

namespace demo {

    class ObjectPrinter {
    public:
        static const std::map<std::type_index, const char *>
        unittypenames;

        static void
        write_map(std::ostream &os, const GameMap *map)
        {
            os << "a Map of size "
               << map->width() << "x" << map->height()
               << " with " << map->unitsCount() << " units";

            int max_units = map->maxUnitsCount();
            if (max_units > 0)
                os << " of " << max_units;
        }

        static void
        write_unit(std::ostream &os, const BaseUnit *unit)
        {
            if (unit) {
                os << "a ";

                auto iter = unittypenames.find({typeid(*unit)});
                os << ((iter != unittypenames.end())
                       ? iter->second
                       : "BaseUnit");

                if (const GamePos &pos = unit->position())
                    os << " at " << pos.x() << "," << pos.y();

                os << " with " << unit->health() << " HP";
            } else {
                os << "(none)";
            }
        }
    };

    class PrintingEventLoop : public events::EventLoop,
                              private ObjectPrinter {
        std::ostream *_os = nullptr;

    public:
        using events::EventLoop::EventLoop;

        std::ostream *ostream() const { return _os; }
        void setOstream(std::ostream *os) { _os = os; }

        void processWithOstream(std::ostream *os);

        virtual void handle(events::Damage *) override;
        virtual void handle(events::Death *) override;
    };

    class DemoSession : public interactive::BasicSession {
        struct CommandEntry {
            const interactive::CommandFactory *factory;
            const char *description;
        };

        static std::map<std::string, CommandEntry> cmdtab;

        class HelpCommand : public interactive::Command {
        public:
            virtual void
            run(Session *, std::ostream &os) const override
            {
                os << "Available commands:" << std::endl;
                for (const auto &p : cmdtab)
                    os << " - " << p.second.description << std::endl;
                os << " - quit" << std::endl;
            }
        };

        static interactive::SimpleCommandFactory<HelpCommand>
        help_factory;

        PrintingEventLoop _evloop;

    public:
        using BasicSession::BasicSession;

        events::EventLoop *evloop() { return &_evloop; }

        virtual const interactive::CommandFactory *
        findCommandFactory(std::string name) const override;

        virtual void
        spin(std::istream &is, std::ostream &os) override;
    };



    class NewMap : public interactive::Command {
        int _w, _h;

    public:
        NewMap(int w, int h) :_w{w}, _h{h} {}

        virtual void
        run(interactive::Session *s, std::ostream &) const override
        {
            s->stack().push_front({new GameMap {_w, _h}, nullptr});
        }
    };

    class NewMapFactory : public interactive::CommandFactory {
    public:
        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            int w, h;
            is >> w >> h;
            if (is.fail()) {
                os << "Failed to read width and height" << std::endl;
                return nullptr;
            }
            return new NewMap {w, h};
        }
    };

    class MapCommand : public interactive::Command {
        int _idx;

    protected:
        int index() const { return _idx; }

        std::list<interactive::Session::Context>::iterator
        map(interactive::Session *s) const
        {
            auto &stack = s->stack();
            auto iter = stack.begin();
            for (int i = 0;
                 i < _idx && iter != stack.end();
                 ++i, ++iter);
            return iter;
        }

    public:
        MapCommand(int idx) :_idx{idx} {}
    };

    template<typename T, int default_idx>
    class MapCommandFactory : public interactive::CommandFactory {
    public:
        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            char c;
            do {
                c = is.get();
            } while (isblank(c));
            is.putback(c);
            if (c == '\n')
                return new T {default_idx};

            int idx;
            is >> idx;
            if (is.fail()) {
                os << "Failed to read map index" << std::endl;
                return nullptr;
            }
            return new T {idx};
        }
    };

    class ExchangeMaps : public MapCommand {
    public:
        using MapCommand::MapCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            auto &stack = s->stack();

            auto maphead = stack.begin();
            if (maphead == stack.end()) {
                os << "Map stack is empty" << std::endl;
                return;
            }

            auto mapiter = map(s);
            if (mapiter == stack.end()) {
                os << "No map #" << index() << std::endl;
                return;
            }

            std::swap(*maphead, *mapiter);
        }
    };

    class PopMap : public MapCommand {
    public:
        using MapCommand::MapCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            auto &stack = s->stack();
            auto mapiter = map(s);
            if (mapiter == stack.end()) {
                os << "No map #" << index() << std::endl;
                return;
            }

            delete mapiter->map;
            stack.erase(mapiter);
        }
    };

    class DupMap : public  MapCommand {
        static BaseUnit *
        get_new_focus(GameMap *map, const GamePos &pos)
        {
            return (pos
                    ? GamePos{map, pos.x(), pos.y()}.cell().unit()
                    : nullptr);
        }

    public:
        using MapCommand::MapCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            auto &stack = s->stack();
            auto mapiter = map(s);
            if (mapiter == stack.end()) {
                os << "No map #" << index() << std::endl;
                return;
            }

            GameMap *new_map = new GameMap {*mapiter->map};

            BaseUnit
                *old_focus = mapiter->focus,
                *new_focus = (old_focus
                              ? get_new_focus(
                                  new_map, old_focus->position())
                              : nullptr);

            stack.push_front({new_map, new_focus});
        }
    };



    class CreateUnit : public interactive::Command {
        const BaseUnitFactory *_factory;
        int _x, _y;

    public:
        CreateUnit(const BaseUnitFactory *factory, int x, int y)
            :_factory{factory}, _x{x}, _y{y} {}

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            GamePos pos {map, _x, _y};
            if (!pos.valid()) {
                os << "Invalid position" << std::endl;
                return;
            }

            if (pos.cell().unit()) {
                os << "Cell already occupied" << std::endl;
                return;
            }

            BaseUnit *unit = _factory->create();
            bool res = unit->moveTo(pos);
            assert(res);
        }
    };

    class CreateUnitFactory : public interactive::CommandFactory {
        std::map<std::string, const BaseUnitFactory *> _typetab;

    public:
        CreateUnitFactory(
            std::map<std::string, const BaseUnitFactory *> typetab)
            :_typetab{std::move(typetab)} {}

        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            std::string word;
            int x, y;
            is >> word >> x >> y;
            if (is.fail()) {
                os << "Failed to read unit class name" << std::endl;
                return nullptr;
            }

            auto iter = _typetab.find(word);
            if (iter == _typetab.end()) {
                os << "Unit type name unknown: `"
                   << word << "'" << std::endl;
                return nullptr;
            }

            return new CreateUnit {iter->second, x, y};
        }
    };

    template<typename T>
    class PositionCommandFactory : public interactive::CommandFactory {
        static bool read(const std::string &s, int *x, int *y)
        {
            std::istringstream ss {s};
            ss >> *x;
            if (ss.fail())
                return false;

            if (ss.get() == std::istringstream::traits_type::eof())
                return false;

            ss >> *y;
            if (ss.fail())
                return false;

            // now we must hit EOF
            return ss.get() == std::istringstream::traits_type::eof();
        }

    public:
        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            std::string buf;
            is >> buf;

            int x, y;
            if (!read(buf, &x, &y)) {
                os << "Failed to read position" << std::endl;
                return nullptr;
            }

            return new T {x, y};
        }
    };

    class PositionCommand : public interactive::Command {
        int _x, _y;

    protected:
        GamePos position(GameMap *map) const { return {map, _x, _y}; }

    public:
        PositionCommand(int x, int y) :_x{x}, _y{y} {}
    };

    class FocusUnit : public PositionCommand {
    public:
        using PositionCommand::PositionCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GamePos pos = position(s->map());
            if (!pos.valid()) { // also when no current map
                os << "Invalid position" << std::endl;
                return;
            }

            BaseUnit *unit = pos.cell().unit();
            if (!unit) {
                os << "No unit there" << std::endl;
                return;
            }

            s->context().focus = unit;
        }
    };

    class MoveUnit : public PositionCommand {
    public:
        using PositionCommand::PositionCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            BaseUnit *unit = s->focus();
            if (!unit) {
                os << "No focused unit" << std::endl;
                return;
            }

            GamePos pos = position(map);
            if (!unit->canMove(pos)) {
                os << "This unit can't move there" << std::endl;
                return;
            }

            if (!unit->moveTo(pos)) {
                os << "That cell is already occupied" << std::endl;
                os << "NOTE: this should've been handled by canMove()"
                   << std::endl;
                return;
            }
        }
    };

    class AttackUnit : public PositionCommand {
    public:
        using PositionCommand::PositionCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            BaseUnit *unit = s->focus();
            if (!unit) {
                os << "No focused unit" << std::endl;
                return;
            }

            GamePos pos = position(map);
            if (!unit->canAttack(pos)) {
                os << "Can't attack there" << std::endl;
                return;
            }

            unit->attack(pos, dynamic_cast<DemoSession *>(s)->evloop());
        }
    };



    class ListMaps : public interactive::Command,
                     private ObjectPrinter {
    public:
        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            auto &stack = s->stack();
            int i = 0;
            for (const interactive::Session::Context &c : stack) {
                os << "#" << i++ << ":\t";
                write_map(os, c.map);
                os << "\tfocus: ";
                write_unit(os, c.focus);
                os << std::endl;
            }
        }
    };

    class MapPrinter {
        static const std::map<std::type_index, char> reprs;

    public:
        static void
        print_cell(const GameCell &cell,
                   std::ostream &os)
        {
            BaseUnit *unit = cell.unit();
            if (!unit) {
                os << '.';
                return;
            }

            auto iter = reprs.find(std::type_index{typeid(*unit)});
            if (iter == reprs.end()) {
                os << '?';
                return;
            }

            os << iter->second;
        }

        static void
        print_line(GameMap::const_iterator b,
                   GameMap::const_iterator e,
                   std::ostream &os)
        {
            for (auto iter = b; iter != e; ++iter)
                print_cell(*iter, os);
            os << std::endl;
        }

        static void
        print_map(const GameMap *map,
                  int x, int y, int w, int h,
                  std::ostream &os)
        {
            int width = map->width();
            auto
                b = map->begin() + (x + width * y),
                e = b + width * h;
            for (auto line_iter = b; line_iter != e; line_iter += width)
                print_line(line_iter, line_iter + w, os);
        }
    };

    class PrintSurroundings : public interactive::Command,
                              private MapPrinter {
        int _cells;

    public:
        PrintSurroundings(int cells) :_cells{cells} {}

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            BaseUnit *unit = s->focus();
            if (!unit) {
                os << "No focused unit" << std::endl;
                return;
            }

            GamePos pos = unit->position();
            assert(pos.valid());

            int x0_u = pos.x() - _cells,
                y0_u = pos.y() - _cells,
                x1_u = pos.x() + _cells + 1,
                y1_u = pos.y() + _cells + 1,
                w = pos.map()->width(),
                h = pos.map()->height(),
                x0 = x0_u >= 0 ? x0_u : 0,
                y0 = y0_u >= 0 ? y0_u : 0,
                x1 = w > x1_u ? x1_u : w,
                y1 = h > y1_u ? y1_u : h;

            print_map(pos.map(), x0, y0, x1 - x0, y1 - y0, os);
        }
    };

    class PrintSurroundingsFactory :
        public interactive::CommandFactory {
    public:
        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            int cells;
            is >> cells;
            if (is.fail()) {
                os << "Failed to read cell count" << std::endl;
                return nullptr;
            }

            return new PrintSurroundings {cells};
        }
    };

    class PrintAll : public interactive::Command,
                     private MapPrinter {
    public:
        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            const GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            print_map(map, 0, 0, map->width(), map->height(), os);
        }
    };

    class ListUnits : public interactive::Command,
                      private ObjectPrinter {
    public:
        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            int n = 0;
            for (const GameCell &cell : *map) {
                BaseUnit *unit = cell.unit();
                if (!unit)
                    continue;

                os << ++n << ". ";
                write_unit(os, unit);
                os << std::endl;
            }
        }
    };

    class UnitInfo : public PositionCommand,
                     private ObjectPrinter {
    public:
        using PositionCommand::PositionCommand;

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            GamePos pos = position(map);
            if (!pos.valid()) {
                os << "Invalid position" << std::endl;
                return;
            }

            BaseUnit *unit = pos.cell().unit();
            if (!unit) {
                os << "No unit there" << std::endl;
                return;
            }

            write_unit(os, unit);
            os << std::endl;
        }
    };

}

#endif
