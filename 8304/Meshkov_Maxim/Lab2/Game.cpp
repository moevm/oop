#include "Game.hpp"

#include "Terrains/WaterTerrain.hpp"
#include "Terrains/StoneTerrain.hpp"
#include "Terrains/ConcreteTerrainFactory.hpp"

constexpr float waterProbability = 0.1f;
constexpr float stoneProbability = 0.1f;

Game::Game()
    : m_field(new Field(0, 0))
{}

void Game::start(int width, int height) {
    m_field.reset(new Field(width, height));
    srand(time(0));
    for (auto [cell, position] : *m_field) {
        auto randomNumber = (float)rand() / RAND_MAX;
        if (randomNumber <= waterProbability) {
            m_field->setTerrain(std::make_shared<ConcreteTerrainFactory<WaterTerrain>>(), position);
        }
        else if (randomNumber <= waterProbability + stoneProbability) {
            m_field->setTerrain(std::make_shared<ConcreteTerrainFactory<StoneTerrain>>(), position);
        }
    }
    // TODO 2 bases with clearing cells and under it also.
}

std::shared_ptr<const Field> Game::getField() const {
    return m_field;
}

void Game::addUnit(const std::shared_ptr<const UnitFactory> &unitFactory, FieldPosition unitPosition) {
    m_field->addUnit(unitFactory, unitPosition);
}

std::set<FieldPosition> Game::findPossibleMoves(FieldPosition unitPosition) const {
    auto unit = m_field->getCell(unitPosition)->getUnit();
    if (unit == nullptr)
        return {};
    return unit->findPossibleMoves(unitPosition, *m_field);
}

void Game::move(FieldPosition unitPosition, FieldPosition targetPosition) {
    auto possibleMoves = findPossibleMoves(unitPosition);
    if (possibleMoves.find(targetPosition) == possibleMoves.end())
        throw std::runtime_error("Impossible move.");
    m_field->moveUnit(unitPosition, targetPosition);
}

std::set<FieldPosition> Game::findPossibleAttacks(FieldPosition unitPosition) const {
    auto unit = m_field->getCell(unitPosition)->getUnit();
    if (unit == nullptr)
        return {};
    return unit->findPossibleAttacks(unitPosition, *m_field);
}

void Game::attack(FieldPosition attackerPosition, FieldPosition victimPosition) {
    auto attacker = m_field->getCell(attackerPosition)->getUnit();
    if (attacker == nullptr)
        return;
    attacker->attack(victimPosition, *m_field);
}
