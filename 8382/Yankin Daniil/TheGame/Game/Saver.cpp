#include <memory>
#include <typeinfo>
#include "Game.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Base/Base.h"


Game::Saver::Saver(std::string& fileName) {
    stream = std::ofstream(fileName);
    if (!stream.is_open())
        throw std::runtime_error("Open saveFile error") ;
}

Game::Saver::~Saver() {
    stream.close();
}

int Game::Saver::save(Game& game) {
    if (game.field == nullptr) {
        return 1;
    }

    stream << "FIELD_START" << std::endl;
    auto fieldSnapshot = std::make_shared<Field::FieldSnapshot>(*game.field);
    stream << *fieldSnapshot;
    stream << "FIELD_END" << std::endl << std::endl << std::endl;

    for (auto player = game.playerVector.begin(); player != game.playerVector.end(); player++) {
        stream << "PLAYER_START" << std::endl;
        auto playerSnapshot = std::make_shared<Player::PlayerSnapshot>(**player);
        stream << *playerSnapshot << std::endl;

        for (auto base = (*player)->baseSet.begin(); base != (*player)->baseSet.end(); base++) {
            stream << "BASE_START" << std::endl;
            auto baseSnapshot = std::make_shared<Base::BaseSnapshot>(**base);
            stream << *baseSnapshot;
            stream << "BASE_END" << std::endl << std::endl;

            for (auto unitIter = (*base)->unitSet.begin(); unitIter != (*base)->unitSet.end(); unitIter++) {
                auto unit = dynamic_cast<Unit*>(*unitIter);
                auto group = dynamic_cast<UnitGroup*>(*unitIter);

                if (unit != nullptr) {
                    stream << "UNIT_START" << std::endl;
                    auto unitSnapshot = std::make_shared<Unit::UnitSnapshot>(*unit);
                    stream << *unitSnapshot;
                    stream << "UNIT_END" << std::endl << std::endl;
                }
                else if (group != nullptr) {
                    stream << "GROUP_START" << std::endl;
                    auto groupSnapshot = std::make_shared<UnitGroup::UnitGroupSnapshot>(*group);
                    stream << *groupSnapshot;
                    stream << "GROUP_END" << std::endl << std::endl;
                }
            }
        }

        stream << "PLAYER_END" << std::endl << std::endl << std::endl;
    }

    for (auto neutral = game.neutralPlayer->neutralSet.begin(); neutral != game.neutralPlayer->neutralSet.end(); neutral++) {
        stream << "NEUTRAL_START" << std::endl;
        auto neutralSnapshot = std::make_shared<NeutralContext::NeutralSnapshot>(**neutral);
        stream << *neutralSnapshot;
        stream << "NEUTRAL_END" << std::endl << std::endl;
    }

    return 0;
}
