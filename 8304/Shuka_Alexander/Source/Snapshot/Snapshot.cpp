#include "snapshot.h"

#include "game.h"

using namespace unit;


void Snapshot::save(const Game& game)
{
    std::ofstream file("save.txt");
    std::stringstream out;

    auto pos = game.playerBase->getPosition();

    out << pos.x << " ";
    out << pos.y << " ";
    out << game.playerBase->getHealthPoints() << " ";
    out << game.playerBase->getNUnits() << "\n";

    for (auto unit : *game.playerUnits) {
        out << unit->draw() << " " << unit->getHealthPoints() << " " <<
               unit->getPosition().x << " " << unit->getPosition().y << "\n";
    }

    pos = game.enemyBase->getPosition();

    out << pos.x << " ";
    out << pos.y << " ";
    out << game.enemyBase->getHealthPoints() << " ";
    out << game.enemyBase->getNUnits() << "\n";

    for (auto unit : *game.enemyUnits) {
        out << unit->draw() << " " << unit->getHealthPoints() << " " <<
               unit->getPosition().x << " " << unit->getPosition().y << "\n";
    }

    out << game.playerGold << " " << game.enemyGold << "\n";

    file << out.str();
    file.close();
}


void Snapshot::load(Game& game)
{
    game.createField();

    game.mediator = std::make_shared<Mediator>(game.field, game.logger);

    game.playerUnits->clear();
    game.enemyUnits->clear();

    std::ifstream file("save.txt");

    std::stringstream stream;

    if (file.is_open()) {
        stream << file.rdbuf();
        file.close();
    }

    Point2D pos;
    double healthPoints = 0;
    size_t nUnits = 0;

    stream >> pos.x;
    stream >> pos.y;
    stream >> healthPoints;
    stream >> nUnits;

    game.playerBase = std::make_shared<Base>(pos, game.mediator,
                                             PLAYER::ONE, healthPoints);
    game.field->addUnit(game.playerBase);

    char unitName = 0;
    for (size_t i = 0; i < nUnits; ++i) {
        stream >> unitName;
        stream >> healthPoints;
        stream >> pos.x;
        stream >> pos.y;

        UnitSnapshot unitSnapshot;
        unitSnapshot.pos = pos;
        unitSnapshot.unit = unitName;
        unitSnapshot.healthPoints = healthPoints;

        auto unit = game.playerBase->createUnit(unitSnapshot);
        game.playerUnits->insert(unit);
        game.field->addUnit(unit);
    }

    stream >> pos.x;
    stream >> pos.y;
    stream >> healthPoints;
    stream >> nUnits;

    game.enemyBase = std::make_shared<Base>(pos, game.mediator,
                                            PLAYER::TWO, healthPoints);
    game.field->addUnit(game.enemyBase);

    for (size_t i = 0; i < nUnits; ++i) {
        stream >> unitName;
        stream >> healthPoints;
        stream >> pos.x;
        stream >> pos.y;

        UnitSnapshot unitSnapshot;
        unitSnapshot.pos = pos;
        unitSnapshot.unit = unitName;
        unitSnapshot.healthPoints = healthPoints;

        auto unit = game.enemyBase->createUnit(unitSnapshot);
        game.enemyUnits->insert(unit);
        game.field->addUnit(unit);
    }

    game.playerFacade = std::make_shared<Facade>(game.mediator, game.playerBase, game.playerUnits,
                                                 game.enemyBase, game.field, game.logger);
    game.enemyFacade = std::make_shared<Facade>(game.mediator, game.enemyBase, game.enemyUnits,
                                                game.playerBase, game.field, game.logger);

    size_t gold = 0;
    stream >> gold;
    game.playerGold = gold;

    stream >> gold;
    game.enemyGold = gold;
}


