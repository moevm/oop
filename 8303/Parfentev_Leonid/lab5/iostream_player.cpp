#include <iostream>
#include <string>
#include <sstream>

#include "game.hpp"
#include "base.hpp"
#include "iostream_player.hpp"
#include "event.hpp"
#include "logging.hpp"


void
IostreamPlayer::addCommand(const std::string &str,
                           IostreamCommand *cmd)
{
    _cmd_tab[str] = cmd;
}

IostreamPlayer::IostreamPlayer(std::string name)
    :Player{name}
{
    addCommand("move", new iostream_commands::Move {});
    addCommand("attack", new iostream_commands::Attack {});
    addCommand("use", new iostream_commands::Use {});
    addCommand("create", new iostream_commands::Create {});
    addCommand("base", new iostream_commands::FindBase {});
    addCommand("units", new iostream_commands::ListUnits {});
    addCommand("describe", new iostream_commands::DescribeAt {});
    addCommand("map", new iostream_commands::PrintMap {});
    addCommand("skip", new iostream_commands::Skip {});
    addCommand("save", new iostream_commands::Save {});
}

bool
IostreamPlayer::takeTurn(const Game *g, Mediator *m, Base *b)
{
    for (;;) {
        std::string cmd_name;
        (*_is) >> cmd_name;

        if (_is->fail()) {
            return false;
        }

        {
            std::ostringstream oss {};
            oss << "User picked action: " << cmd_name;
            emit(new events::UserActionEvent {this, oss.str()});
        }

        auto iter = _cmd_tab.find(cmd_name);
        if (iter == _cmd_tab.end()) {
            std::ostringstream oss {};
            oss << "Unknown command: \"" << cmd_name << "\"";
            emit(new events::UserActionEvent {this, oss.str()});
            (*_os) << oss.str() << "\n";
            continue;
        }

        if (iter->second->execute(g, this, m, b)) {
            break;
        }
    }

    return true;
}

int
IostreamPlayer::readInt()
{
    int x;
    (*_is) >> x;
    return x;
}

Unit *
IostreamPlayer::readUnitId(Base *b)
{
    int id = readInt();
    Unit *u = b->getUnitById(id);
    if (!u) {
        (*_os) << "No such unit: " << id << "\n";
    }

    return u;
}

Vec2
IostreamPlayer::readVec2()
{
    int x, y;
    (*_is) >> x >> y;
    return {x, y};
}

std::string
IostreamPlayer::readString()
{
    std::string s;
    (*_is) >> s;
    return s;
}

void
IostreamPlayer::store(std::ostream &os) const
{
    os << "iostream_player\n" << name() << "\n";
}

bool
IostreamPlayer::restore(std::istream &is,
                        RestorerTable *tab)
{
    Player::restore(is, tab);

    // We can’t serialize/deserialize IO streams
    setOstream(std::cout);
    setIstream(std::cin);
    return true;
}
