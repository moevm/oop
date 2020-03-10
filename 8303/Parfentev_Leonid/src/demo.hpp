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
#include "map.hpp"
#include "unit.hpp"
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
                os << " out of " << max_units;
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

                if (unit->pointSet())
                    os << " at " << unit->point().x()
                       << "," << unit->point().y();

                os << " with " << unit->health() << " HP";
            } else {
                os << "(none)";
            }
        }
    };

    class DemoSession : public interactive::BasicSession,
                        public events::EventLoop,
                        private ObjectPrinter{
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
                os << " - help -- Print this help message"
                   << std::endl;
                os << " - quit -- Quit"
                   << std::endl;
            }
        };

        static interactive::SimpleCommandFactory<HelpCommand>
        help_factory;

        std::ostream *_os;

    public:
        using BasicSession::BasicSession;

        virtual const interactive::CommandFactory *
        findCommandFactory(std::string name) const override;

        virtual void
        spin(std::istream &is, std::ostream &os) override;

        virtual void
        handle(events::Damage *) override;
        virtual void
        handle(events::Death *) override;
    };



    class NewMap : public interactive::Command {
        int _w, _h;

    public:
        NewMap(int w, int h) :_w{w}, _h{h} {}

        virtual void
        run(interactive::Session *s, std::ostream &) const override
        {
            s->resetMap({new GameMap {_w, _h}});
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

    class SetMaxUnits : public interactive::Command {
        int _n;

    public:
        SetMaxUnits(int n) :_n{n} {}

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            if (!map->setMaxUnitsCount(_n)) {
                os << "Failed (currently " << map->unitsCount()
                   << " units)" << std::endl;
                return;
            }
        }
    };

    class SetMaxUnitsFactory : public interactive::CommandFactory {
    public:
        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            int n;
            is >> n;

            if (is.fail()) {
                os << "Failed to read new max number of units"
                   << std::endl;
                return nullptr;
            }

            if (n <= 0) {
                os << "Max number of units must be positive"
                   << std::endl;
                return nullptr;
            }

            return new SetMaxUnits {n};
        }
    };

    class UnsetMaxUnits : public interactive::Command {
    public:
        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            map->setMaxUnitsCount(0);
        }
    };



    class PointCommand : public interactive::Command {
        int _x, _y;

    protected:
        Point point() const { return {_x, _y}; }

        // TODO: runWithMapIter(..., MapIter iter);
        // overridden ‘run’ that checks that position is valid

        virtual void
        runWithMapIter(interactive::Session *s,
                       std::ostream &os,
                       MapIter iter) const =0;

    public:
        PointCommand(int x, int y) :_x{x}, _y{y} {}

        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            GameMap *map = s->map();
            if (!map) {
                os << "No current map" << std::endl;
                return;
            }

            Point pt = point();
            if (!map->ptValid(pt)) {
                os << "Invalid point" << std::endl;
                return;
            }

            MapIter iter = map->iterAt(pt);
            runWithMapIter(s, os, iter);
        }
    };

    class CreateUnit : public PointCommand {
        const BaseUnitFactory *_factory;

    protected:
        virtual void
        runWithMapIter(interactive::Session *,
                       std::ostream &os,
                       MapIter iter) const override
        {
            if (iter->unit()) {
                os << "Cell already occupied" << std::endl;
                return;
            }

            BaseUnit *unit = _factory->create();
            if (!iter.map()->placeUnit(iter.point(), unit)) {
                os << "Failed to place unit" << std::endl;
                delete unit;
                return;
            }
        }

    public:
        CreateUnit(const BaseUnitFactory *factory, int x, int y)
            :PointCommand{x, y}, _factory{factory} {}
    };

    class PointReader {
    public:
        static bool read_point(const std::string &s, int *x, int *y)
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
    };

    class CreateUnitFactory : public interactive::CommandFactory,
                              private PointReader {
        std::map<std::string, const BaseUnitFactory *> _typetab;

    public:
        CreateUnitFactory(
            std::map<std::string, const BaseUnitFactory *> typetab)
            :_typetab{std::move(typetab)} {}

        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            std::string word, pos;
            is >> word >> pos;
            if (is.fail()) {
                os << "Failed to read unit class name or position"
                   << std::endl;
                return nullptr;
            }

            auto iter = _typetab.find(word);
            if (iter == _typetab.end()) {
                os << "Unit type name unknown: `"
                   << word << "'" << std::endl;
                return nullptr;
            }

            int x, y;
            if (!read_point(pos, &x, &y)) {
                os << "Failed to read initial position" << std::endl;
                return nullptr;
            }

            return new CreateUnit {iter->second, x, y};
        }
    };

    template<typename T>
    class PointCommandFactory : public interactive::CommandFactory,
                                private PointReader {

    public:
        virtual interactive::Command *
        create(std::istream &is, std::ostream &os) const override
        {
            std::string buf;
            is >> buf;

            int x, y;
            if (!read_point(buf, &x, &y)) {
                os << "Failed to read position" << std::endl;
                return nullptr;
            }

            return new T {x, y};
        }
    };

    class FocusUnit : public PointCommand {
    protected:
        virtual void
        runWithMapIter(interactive::Session *s,
                       std::ostream &os,
                       MapIter iter) const override
        {
            BaseUnit *unit = iter->unit();
            if (!unit) {
                os << "No unit there" << std::endl;
                return;
            }

            s->setFocus(unit);
        }

    public:
        using PointCommand::PointCommand;
    };

    class MoveUnit : public PointCommand {
    protected:
        virtual void
        runWithMapIter(interactive::Session *s,
                       std::ostream &os,
                       MapIter iter) const override
        {
            BaseUnit *unit = s->focus();
            if (!unit) {
                os << "No focused unit" << std::endl;
                return;
            }

            if (!unit->canMove(iter)) {
                os << "This unit can't move there" << std::endl;
                return;
            }

            GameMap *map = iter.map();
            if (!map->placeUnit(iter.point(),
                                map->removeFrom(
                                    unit->point()))) {
                os << "That cell is already occupied" << std::endl;
                os << "NOTE: this should've been handled by canMove()"
                   << std::endl;
                return;
            }
        }

    public:
        using PointCommand::PointCommand;
    };

    class AttackUnit : public PointCommand {
    protected:
        virtual void
        runWithMapIter(interactive::Session *s,
                       std::ostream &os,
                       MapIter iter) const override
        {
            BaseUnit *unit = s->focus();
            if (!unit) {
                os << "No focused unit" << std::endl;
                return;
            }

            if (!unit->canAttack(iter)) {
                os << "Can't attack there" << std::endl;
                return;
            }

            unit->attack(iter, dynamic_cast<DemoSession *>(s));
        }

    public:
        using PointCommand::PointCommand;
    };



    class Status : public interactive::Command,
                   private ObjectPrinter {
    public:
        virtual void
        run(interactive::Session *s, std::ostream &os) const override
        {
            os << "Map: ";
            write_map(os, s->map());
            os << std::endl << "Focus: ";
            write_unit(os, s->focus());
            os << std::endl;
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

            Point pt = unit->point();
            assert(map->ptValid(pt));

            int x0_u = pt.x() - _cells,
                y0_u = pt.y() - _cells,
                x1_u = pt.x() + _cells + 1,
                y1_u = pt.y() + _cells + 1,
                w = map->width(),
                h = map->height(),
                x0 = std::max(x0_u, 0),
                y0 = std::max(y0_u, 0),
                x1 = std::min(x1_u, w),
                y1 = std::min(y1_u, h);

            print_map(map, x0, y0, x1 - x0, y1 - y0, os);
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

    class UnitInfo : public PointCommand,
                     private ObjectPrinter {
    protected:
        virtual void
        runWithMapIter(interactive::Session *,
                       std::ostream &os,
                       MapIter iter) const override
        {
            BaseUnit *unit = iter->unit();
            if (!unit) {
                os << "No unit there" << std::endl;
                return;
            }

            write_unit(os, unit);
            os << std::endl;
        }

    public:
        using PointCommand::PointCommand;
    };

}

#endif
