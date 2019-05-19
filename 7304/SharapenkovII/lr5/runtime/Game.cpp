//
// Created by smokfyz on 12.04.19.
//
#include <iostream>
#include "Game.h"
#include "../logger/Logger.h"

Game::Game() {
    gui = make_unique<GUI>();
    field = unique_ptr<Field>(nullptr);

    current_turn_player = 0;

    current_cell = shared_ptr<Cell>(nullptr);

    Logger &logger = Logger::getLogger();
    logger.setLogger(make_unique<FileLogger>());
    logger.loggingMode(true);
}

Game &Game::getGame() {
    static Game instance;

    return instance;
}

void Game::run() { gui->run(); }

void Game::nextTurn() {

    unsigned num_of_players = players.size();

    if(num_of_players == current_turn_player + 1 || !num_of_players) current_turn_player = 0;
    else current_turn_player++;

    updateImps();
    clearPickCell();
    resetUnits();

    Logger &logger = Logger::getLogger();

    logger.write("Next turn. Current player: " + players[current_turn_player]->getName());
}

void Game::createUnit(Coord c, string unit_type, shared_ptr<Player> player) {
    player->createUnit(c, unit_type);

    Logger &logger = Logger::getLogger();
    logger.write(
            "Create Unit. Type: " + unit_type + "; Coord: " + "(" + to_string(c.getX()) + "," + to_string(c.getY()) +
            ")");
}

void Game::clearUnits() {
    for (auto &player : players) {
        auto units = player->getUnits();
        for (auto &unit : units) {
            if (!unit->getPosition()->hasUnit())
                player->getUnits().erase(std::remove(player->getUnits().begin(), player->getUnits().end(), unit),
                                         player->getUnits().end());
        }
    }
}

shared_ptr<Unit> Game::getUnit(Coord) {

}

void Game::moveUnit(shared_ptr<Cell> from, shared_ptr<Cell> to, unsigned energy_loss) {
    to->setUnit(from->getUnit());
    from->deleteUnit();
    to->getUnit()->setPosition(to);
    to->getUnit()->setEnergy(energy_loss);

    Logger &logger = Logger::getLogger();
    logger.write(
            "Move Unit. From: (" + to_string(from->getX()) + "," + to_string(from->getY()) +
            "); To: (" + to_string(to->getX()) + "," + to_string(to->getY()) + ")");
}

void Game::attackUnit(shared_ptr<Cell> from, shared_ptr<Cell> to) {
    shared_ptr<Unit >unit1 = from->getUnit();
    shared_ptr<Unit >unit2 = to->getUnit();

    unit1->attackUnit(unit2);

    Logger &logger = Logger::getLogger();
    logger.write(
            "Attack Unit. From: (" + to_string(from->getX()) + "," + to_string(from->getY()) +
            "); To: (" + to_string(to->getX()) + "," + to_string(to->getY()) + ")");
}

void Game::resetUnits() {
    for(auto &player : players)
        player->resetUnits();
}

void Game::createImp(Coord c, string imp_type) {
    ImpedimentOrchestrator &imp_orch = field->getImpOrch();
    imp_orch.createImp(c, imp_type);
}

void Game::deleteImp(Coord c) {
    ImpedimentOrchestrator &imp_orch = field->getImpOrch();

    imp_orch.deleteImp(field->getCell(c)->getImp());
}

vector<shared_ptr<Impediment>> &Game::getImps() { return field->getImps(); }

void Game::updateImps() {
    ImpedimentOrchestrator &imps_orch = field->getImpOrch();

    imps_orch.updateImps();
}

void Game::createField(unsigned field_size) { field = make_unique<Field>(field_size); }

Field &Game::getField() { return *field; }

vector<shared_ptr<Player>>& Game::getPlayers() { return players; }

shared_ptr<Player> Game::getCurrentPlayer() { return players[current_turn_player]; }

void Game::addPlayer(shared_ptr<Player> &player) {

    players.push_back(player);

    Logger &logger = Logger::getLogger();
    logger.write("Create Player. Name: " + player->getName() + "; Color: " + player->getColor() + ";");
}

void Game::pickCell(Coord c) {

    if (hasPickCell() && getCurrentPlayer()->hasUnit(getCurrentCell()->getUnit()) &&
        !getCell(c)->hasUnit()) {
        if (getCurrentPlayer()->hasPath(getCell(c))) {

            moveUnit(getCurrentCell(), getCell(c),
                          getCurrentPlayer()->getEnergyLoss(getCell(c)));

            getCurrentPlayer()->clearPaths();
            clearPickCell();

            return;
        }
    } else if (hasPickCell() && getCell(c)->hasUnit() &&
               !getCurrentPlayer()->hasUnit(getCell(c)->getUnit()) &&
               getCurrentPlayer()->hasPath(getCell(c))) {


        attackUnit(getCurrentCell(), getCell(c));

        clearUnits();
        getCurrentPlayer()->clearPaths();
        clearPickCell();

        return;
    }

    current_cell = field->getCell(c);

    getCurrentPlayer()->clearPaths();

    if(current_cell->hasUnit() && getCurrentPlayer()->hasUnit(current_cell->getUnit()))
        getCurrentPlayer()->findPaths(current_cell, current_cell->getUnit()->getEnergy(), 6);

    if(current_cell->hasImp()) {

    }

    Logger &logger = Logger::getLogger();
    logger.write("Pick Cell. Coord: " + to_string(current_cell->getX()) + ", " + to_string(current_cell->getX()) + ");");
}

bool Game::hasPickCell() { return !!current_cell; }

void Game::clearPickCell() { current_cell.reset(); }

shared_ptr<Cell> Game::getCell(Coord c) { return field->getCell(c); }

shared_ptr<Cell> Game::getCurrentCell() { return current_cell; }
