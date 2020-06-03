#include "game_rule.hpp"
#include "units/unit.hpp"
#include "tiles/fortress.hpp"
#include "ui.hpp"
#include "tiles/water.hpp"
#include "units/citadel.hpp"
#include "units/neutrals/fair.hpp"
#include "units/neutrals/farmer.hpp"
#include "units/neutrals/sheep.hpp"
#include "units/neutrals/villager.hpp"
#include "exceptions/strategy_exception.hpp"

bool GameRule::isGameEnded () {
    return gameHandler->findUnit(redCitadelId) == nullptr || gameHandler->findUnit(blueCitadelId) == nullptr;
}

void GameRule::onGameStart (GameRule::GameHandler* gameHandler) {
    frameCount = 0;
    this->gameHandler = gameHandler;

    gameHandler->setSize(sizeX, sizeY);
    //gameFieldHandler->setTile(0, 0, &water);

    int fortressSizeX = sizeX * 0.2;
    int fortressSizeY = sizeY * 0.2;

    int fortressOffsetX = sizeX * 0.1;
    int fortressOffsetY = sizeY * 0.1;

    int fortressAOffsetX = fortressOffsetX;
    int fortressAOffsetY = fortressOffsetY;

    Unit *redCitadel = plaseFortress(
            fortressAOffsetX,
            fortressAOffsetY,
            fortressAOffsetX + fortressSizeX,
            fortressAOffsetY + fortressSizeY,
            RED
    );

    int fortressBOffsetX = sizeX - 1 - fortressSizeX - fortressOffsetX;
    int fortressBOffsetY = sizeY - 1 - fortressSizeY - fortressOffsetY;

    Unit *blueCitadel = plaseFortress(
            fortressBOffsetX,
            fortressBOffsetY,
            fortressBOffsetX + fortressSizeX,
            fortressBOffsetY + fortressSizeY,
            BLUE
    );

    redCitadelId = redCitadel->getId();
    blueCitadelId = blueCitadel->getId();

    redCitadel->setTargetXY(blueCitadel->getX(), blueCitadel->getY());
    blueCitadel->setTargetXY(redCitadel->getX(), redCitadel->getY());
    // Design
    fillRect(0, 0, 0, sizeY - 1, Water::id);
    fillRect(sizeX - 1, 0, sizeX - 1, sizeY - 1, Water::id);

    plaseVillage(sizeX / 5 * 4, sizeY / 5);
    plaseVillage(sizeX / 5, sizeY / 5 * 4);
}

void GameRule::onGameUpdate () {
    frameCount++;
    UI* ui = gameHandler->getUI();
    if (ui == nullptr) return;
    Unit* r = gameHandler->findUnit(redCitadelId);
    if (r) ui->displayPixel(r->getTargetX(), r->getTargetY(), 'R');
    Unit* b = gameHandler->findUnit(blueCitadelId);
    if (b) ui->displayPixel(b->getTargetX(), b->getTargetY(), 'B');
    gameHandler->getLogger().log("-F " + to_string(frameCount));
    // Your custom ads and logic here
}

void GameRule::fillRect (int minX, int minY, int maxX, int maxY, char tileId) {
    for(int y = minY; y <= maxY; y++) {
        for(int x = minX; x <= maxX; x++) {
            gameHandler->setTile(x, y, tileId);
        }
    }
}

void GameRule::plaseVillage (int x, int y) {
    fillRect(x, y, x, y, Water::id);

    // Neutral
    plaseNeutral(x + 1, y, Fair::type);
    plaseNeutral(x - 1, y, Farmer::type);
    plaseNeutral(x, y + 1, Sheep::type);
    plaseNeutral(x, y - 1, Villager::type);
}

void GameRule::plaseNeutral (int x, int y, string type) {
    Unit* u = gameHandler->createUnit(type);
    if (u == nullptr)
        return;
    u->setXY(x, y);
    u->setTargetXY(x, y);
}

Unit* GameRule::plaseFortress (int minX, int minY, int maxX, int maxY, Team team) {
    fillRect(minX, minY, maxX, maxY, Fortress::id);
    Unit* citadel = gameHandler->createUnit(Citadel::type);
    if (citadel == nullptr) throw strategyException("Can't create citadel");
    citadel->setTeam(team);
    citadel->setXY((int)((minX + maxX) * 0.5), (int)((minY + maxY) * 0.5));
    return citadel;
}

Unit* GameRule::getCitadel (Team team) {
    switch (team) {
        case RED:
            return gameHandler->findUnit(redCitadelId);
        case BLUE:
            return gameHandler->findUnit(blueCitadelId);
        default:
            return nullptr;
    }
}

int GameRule::getMaxUnits() {
    return maxUnits;
}

void GameRule::reset() {

}

