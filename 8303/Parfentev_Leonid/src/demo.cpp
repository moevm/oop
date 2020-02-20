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

    std::map<std::type_index, char>
    MapPrinter::reprs = {
        {{typeid(units::Swordsman)}, 's'},
        {{typeid(units::Spearsman)}, 'S'},
        {{typeid(units::Rider)}, 'R'},
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
        {"listmaps",
         {new interactive::SimpleCommandFactory<demo::ListMaps>{},
         "listmaps"}},

        {"create",
         {new demo::CreateUnitFactory{{
                     {"swordsman",
                      new BasicUnitFactory<units::Swordsman>{}},
                     {"spearsman",
                      new BasicUnitFactory<units::Spearsman>{}},
                     {"rider",
                      new BasicUnitFactory<units::Rider>{}},
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

        {"show",
         {new demo::PrintSurroundingsFactory{},
          "show CELLS"}},
        {"showall",
         {new interactive::SimpleCommandFactory<demo::PrintAll>{},
          "showall"}},
    };

}
