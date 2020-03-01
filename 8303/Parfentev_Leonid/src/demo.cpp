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
         {new demo::NewMapFactory{},
          "newmap WIDTH HEIGHT"}},
        {"exchmap",
         {new demo::MapCommandFactory<demo::ExchangeMaps, 1>{},
         "exchmap [INDEX]"}},
        {"popmap",
         {new demo::MapCommandFactory<demo::PopMap, 0>{},
         "popmap [INDEX]"}},
        {"dupmap",
         {new demo::MapCommandFactory<demo::DupMap, 0>{},
         "dupmap [INDEX]"}},

        {"create",
         {new demo::CreateUnitFactory{{
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
          "create CLASS X Y"}},
        {"focus",
         {new demo::PositionCommandFactory<demo::FocusUnit>{},
          "focus POSITION"}},
        {"moveto",
         {new demo::PositionCommandFactory<demo::MoveUnit>{},
          "moveto DESTINATION"}},
        {"attack",
         {new demo::PositionCommandFactory<demo::AttackUnit>{},
          "attack POSITION"}},
        {"delete",
         {new interactive::SimpleCommandFactory<demo::DeleteUnit>{},
          "delete"}},

        {"show",
         {new demo::PrintSurroundingsFactory{},
          "show CELLS"}},
        {"showall",
         {new interactive::SimpleCommandFactory<demo::PrintAll>{},
          "showall"}},
        {"listmaps",
         {new interactive::SimpleCommandFactory<demo::ListMaps>{},
         "listmaps"}},
        {"list",
         {new interactive::SimpleCommandFactory<demo::ListUnits>{},
          "list"}},
        {"info",
         {new demo::PositionCommandFactory<demo::UnitInfo>{},
          "info POSITION"}},
    };

    void
    PrintingEventLoop::processWithOstream(std::ostream *os)
    {
        setOstream(os);
        process();
    }

    void
    PrintingEventLoop::handle(events::Damage *dmg)
    {
        if (!_os)
            return;

        write_unit(*_os, dmg->unit);
        *_os << " takes damage: " << dmg->dmg << std::endl;
    }

    void
    PrintingEventLoop::handle(events::Death *d)
    {
        if (!_os)
            return;

        write_unit(*_os, d->unit);
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

        _evloop.processWithOstream(&os);
    }

}
