#include <typeinfo>
#include <typeindex>
#include <string>
#include <map>

#include "interactive.hpp"
#include "unit_types.hpp"
#include "demo.hpp"

namespace demo {

    interactive::SimpleCommandFactory<DemoSession::HelpCommand>
    DemoSession::help_factory {};

    const std::map<std::type_index, char>
    MapPrinter::reprs = {
        {{typeid(units::Swordsman)}, 's'},
        {{typeid(units::Spearsman)}, 'S'},
        {{typeid(units::Rider)}, 'R'},
        {{typeid(units::Archer)}, 'a'},
        {{typeid(units::Slinger)}, 'l'},
        {{typeid(units::Onager)}, 'O'},
        {{typeid(units::BoltThrower)}, 'B'},
    };

    const std::map<std::type_index, const char *>
    ObjectPrinter::unittypenames = {
        {{typeid(units::Swordsman)}, "Swordsman"},
        {{typeid(units::Spearsman)}, "Spearsman"},
        {{typeid(units::Rider)}, "Rider"},
        {{typeid(units::Archer)}, "Archer"},
        {{typeid(units::Slinger)}, "Slinger"},
        {{typeid(units::Onager)}, "Onager"},
        {{typeid(units::BoltThrower)}, "Bolt thrower"},
    };

    std::map<std::string, DemoSession::CommandEntry>
    DemoSession::cmdtab = {
        {"newmap",
         {new NewMapFactory{},
          "newmap WIDTH HEIGHT -- Create new empty map of size WIDTHxHEIGHT"
         }},
        {"setlimit",
         {new SetMaxUnitsFactory{},
          "setlimit N -- Set a limit of N units on map"}},
        {"unsetlimit",
         {new interactive::SimpleCommandFactory<UnsetMaxUnits>{},
          "unsetlimit -- Unset the units count limit"}},

        {"create",
         {new CreateUnitFactory{{
                     {"swordsman",
                      new BasicUnitFactory<units::Swordsman>{}},
                     {"spearsman",
                      new BasicUnitFactory<units::Spearsman>{}},
                     {"rider",
                      new BasicUnitFactory<units::Rider>{}},
                     {"archer",
                      new BasicUnitFactory<units::Archer>{}},
                     {"slinger",
                      new BasicUnitFactory<units::Slinger>{}},
                     {"onager",
                      new BasicUnitFactory<units::Onager>{}},
                     {"boltthrower",
                      new BasicUnitFactory<units::BoltThrower>{}},
                 }},
          "create CLASS POSITION -- Create unit of class CLASS at POSITION"
         }},
        {"focus",
         {new PointCommandFactory<FocusUnit>{},
          "focus POSITION -- Focus on the unit at POSITION"
         }},
        {"moveto",
         {new PointCommandFactory<MoveUnit>{},
          "moveto DESTINATION -- Make the focused unit move to DESTINATION"
         }},
        {"attack",
         {new PointCommandFactory<AttackUnit>{},
          "attack POSITION -- Make the focused unit attack a unit at POSITION"
         }},

        {"print",
         {new PrintSurroundingsFactory{},
          "print N -- Display everything within N cells from the focused unit"
         }},
        {"printall",
         {new interactive::SimpleCommandFactory<PrintAll>{},
          "printall -- Display the entire map"
         }},
        {"status",
         {new interactive::SimpleCommandFactory<Status>{},
          "status -- Describe the current map and focused unit"
         }},
        {"list",
         {new interactive::SimpleCommandFactory<ListUnits>{},
          "list -- Print a list of units on the map"
         }},
        {"info",
         {new PointCommandFactory<UnitInfo>{},
          "info POSITION -- Describe the unit at POSITION"
         }},
    };

    void
    DemoSession::handle(events::Damage *dmg)
    {
        assert(_os);

        write_unit(*_os, dmg->iter->unit());
        *_os << " takes damage: " << dmg->dmg << std::endl;
    }

    void
    DemoSession::handle(events::Death *d)
    {
        assert(_os);

        BaseUnit *unit = d->iter->unit();
        // assume events only happen on the topmost map in stack
        if (unit == focus())
            setFocus(nullptr);

        write_unit(*_os, unit);
        *_os << " dies." << std::endl;
    }

    const interactive::CommandFactory *
    DemoSession::findCommandFactory(std::string name) const
    {
        if (name == "help")
            return &help_factory;

        auto iter = cmdtab.find(name);
        if (iter == cmdtab.end())
            return BasicSession::findCommandFactory(name);

        return iter->second.factory;
    }

    void
    DemoSession::spin(std::istream &is, std::ostream &os)
    {
        Session::spin(is, os);
        _os = &os;
        EventLoop::process();
    }

}
