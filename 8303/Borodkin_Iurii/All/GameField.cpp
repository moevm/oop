#include "GameField.h"
#include <QDebug>

GameField::GameField()
{
    field = nullptr;

}

GameField::GameField(int n, int m, int _maxNumUnits, int _maxNumUnitsBase) : Field(n, m, _maxNumUnits, _maxNumUnitsBase)
{
   double x1 = 0.0, y1 = 0.0;

    for (size_t i = 0; i < size_t(n); i++)
    {
        gameField.emplace_back();
        for (size_t j = 0; j < size_t(m); j++)
        {
            gameField[i].emplace_back(field[i][j], QRectF(x1, y1, 728.0 / m, 728.0 / n), QPen(Qt::black));
            gameField[i].back().landscape = nullptr;
            x1 += 728.0 / m;
        }
        y1 += 728.0 / n;
        x1 = 0.0;
    }
}

void GameField::addUnit(Unit* obj, const Coordinates &coords)
{
    size_t y = size_t(coords.y);
    size_t x = size_t(coords.x);
    if (!(y < fieldHeight && x < fieldWidth) ||
          gameField[y][x].landscape->deathCell() ||
         !gameField[y][x].landscape->canStandUnit())
        return;

    if (!field[y][x]) {
        if (numUnits == maxNumUnits)
            return;
        field[y][x] = obj;
        numUnits++;
    } else if (field[y][x]->type() == "Base") {

        // USING PATTERN OBSERVER
        /*
           qDebug() << "Before:";
           MonitorBase mBase;
           Reflector ref;

           mBase.addObserver(ref);
           mBase.resetBase(*dynamic_cast<Base*>(field[y][x]));
        */
        //PATTERN OBSERVER END

        field[y][x]->createUnit(obj);

        //CHECK CHANGES
        //qDebug() << "\nAfter:";
        //mBase.resetBase(*dynamic_cast<Base*>(field[y][x]));
        //qDebug();
    }
}

void GameField::addBase(Base* obj, const Coordinates &coords)
{
    size_t y = size_t(coords.y);
    size_t x = size_t(coords.x);
    if (!(y + 1 < fieldHeight && x + 1 < fieldWidth))
        return;

    if (gameField[y][x].canPlaceBuild())
    {
        field[y][x] = obj;
        field[y + 1][x] = obj;
        field[y][x + 1] = obj;
        field[y + 1][x + 1] = obj;
        clones[obj] = {&field[y][x], &field[y+1][x], &field[y][x+1], &field[y+1][x+1]};
        countBase++;
    }
}

std::vector <Object**> GameField::getClones(Coordinates c)
{
    return clones[(*this)[size_t(c.y)][size_t(c.x)].obj];
}

void GameField::delObject(const Coordinates &coords)
{
    size_t y = size_t(coords.y);
    size_t x = size_t(coords.x);
    if (!(y < fieldHeight && x < fieldWidth))
        return;

    auto& deletedObject = field[y][x];

    if (deletedObject->type() == "Base") {

        //for save command
        //delete deletedObject;
        countBase--;

        for (auto clone : clones[deletedObject])
            *clone = nullptr;

        clones[deletedObject].clear();

    } else {

        numUnits -= deletedObject
                     ? 1 : 0;

        //for save command
        //delete deletedObject;

        deletedObject = nullptr;
    }
}

//trying buff unit
void buffUnit(Object* unit, Pack** pack)
{
    auto pPack = *pack;
    if (pPack->type() == "Armor") {
        Strategy <ArmorStrategy> client;
        client.useStrategy(unit, pack);
    } else if (pPack->type() == "Mana") {
        Strategy <ManaStrategy> client;
        client.useStrategy(unit, pack);
    } else if (pPack->type() == "Damage") {
        Strategy <DamageStrategy> client;
        client.useStrategy(unit, pack);
    } else if (pPack->type() == "Health") {
        Strategy <HealthStrategy> client;
        client.useStrategy(unit, pack);
    }
}

bool GameField::move(const Coordinates &coords, const Coordinates &to)
{
    if (!((coords.y < int(fieldHeight) && coords.y >= 0) &&
          (coords.x < int(fieldWidth) && coords.x >= 0)) ||
          (!field[coords.y][coords.x]) || field[to.y][to.x] ||
          !gameField[size_t(coords.y)][size_t(coords.x)].landscape->canMove() ||
          !gameField[size_t(to.y)][size_t(to.x)].landscape->canStandUnit())
        return false;

    size_t j = size_t(coords.x);
    size_t i = size_t(coords.y);
    int distance = int(gameField[i][j].obj->travelDistance());
    std::vector <Pack**> packs;

    //DOWN
    std::pair<size_t, size_t> stopCoords = {UINT_MAX, UINT_MAX};
    for (int _i = int(i) - 1; _i >= int(i) - distance; _i--)
    {
        if (_i < 0 || size_t(_i) >= height() || field[_i][j]) break;

        auto &cell = gameField[size_t(_i)][j];

        packs.push_back(&cell.pack);
        if (!cell.landscape->canMove() && stopCoords.first == UINT_MAX)
            stopCoords = {_i, j};

        if (to.y == _i && to.x == int(j))
        {
            for (auto &pack : packs)
                if (*pack)
                    buffUnit(field[coords.y][coords.x], pack);

            if (cell.landscape->deathCell())
            {
                LavaProxy lp;
                lp.kill(field[coords.y][coords.x]);
                numUnits--;
            }

            if (stopCoords.first == UINT_MAX)
                std::swap(field[coords.y][coords.x], field[to.y][to.x]);
            else
                std::swap(field[coords.y][coords.x], field[stopCoords.first+1][stopCoords.second]);

            packs.clear();
            return true;
        }
    }

    packs.clear();
    stopCoords = {UINT_MAX, UINT_MAX};

    //UP
    for (int _i = int(i) + 1; _i <= int(i) + distance; _i++)
    {
        if (_i < 0 || size_t(_i) >= height() || field[_i][j]) break;

        auto &cell = gameField[size_t(_i)][j];

        packs.push_back(&cell.pack);
        if (!cell.landscape->canMove() && stopCoords.first == UINT_MAX)
            stopCoords = {_i, j};

        if (to.y == _i && to.x == int(j))
        {
            for (auto &pack : packs)
                if (*pack)
                    buffUnit(field[coords.y][coords.x], pack);

            if (cell.landscape->deathCell())
            {
                LavaProxy lp;
                lp.kill(field[coords.y][coords.x]);
                numUnits--;
            }

            if (stopCoords.first == UINT_MAX)
                std::swap(field[coords.y][coords.x], field[to.y][to.x]);
            else
                std::swap(field[coords.y][coords.x], field[stopCoords.first-1][stopCoords.second]);

            packs.clear();
            return true;
        }
    }

    packs.clear();
    stopCoords = {UINT_MAX, UINT_MAX};

    //LEFT
    for (int _j = int(j) - 1; _j >= int(j) - distance; _j--)
    {
        if (_j < 0 || size_t(_j) >= width() || field[i][_j]) break;

        auto &cell = gameField[i][size_t(_j)];

        packs.push_back(&cell.pack);
        if (!cell.landscape->canMove() && stopCoords.first == UINT_MAX)
            stopCoords = {i, _j};

        if (to.y == int(i) && to.x == _j)
        {
            for (auto &pack : packs)
                if (*pack)
                    buffUnit(field[coords.y][coords.x], pack);

            if (cell.landscape->deathCell())
            {
                LavaProxy lp;
                lp.kill(field[coords.y][coords.x]);
                numUnits--;
            }

            if (stopCoords.first == UINT_MAX)
                std::swap(field[coords.y][coords.x], field[to.y][to.x]);
            else
                std::swap(field[coords.y][coords.x], field[stopCoords.first][stopCoords.second+1]);

            packs.clear();
            return true;
        }
    }

    packs.clear();
    stopCoords = {UINT_MAX, UINT_MAX};

    //RIGHT
    for (int _j = int(j) + 1; _j <= int(j) + distance; _j++)
    {
        if (_j < 0 || size_t(_j) >= width() || field[i][_j]) break;

        auto &cell = gameField[i][size_t(_j)];

        packs.push_back(&cell.pack);
        if (!cell.landscape->canMove() && stopCoords.first == UINT_MAX)
            stopCoords = {i, _j};

        if (to.y == int(i) && to.x == _j)
        {
            for (auto &pack : packs)
                if (*pack)
                    buffUnit(field[coords.y][coords.x], pack);

            if (cell.landscape->deathCell())
            {
                LavaProxy lp;
                lp.kill(field[coords.y][coords.x]);
                numUnits--;
            }

            if (stopCoords.first == UINT_MAX)
                std::swap(field[coords.y][coords.x], field[to.y][to.x]);
            else
                std::swap(field[coords.y][coords.x], field[stopCoords.first][stopCoords.second-1]);

            packs.clear();
            return true;
        }
    }

    packs.clear();

    return false;
}

bool GameField::attack(const Coordinates &damaging, const Coordinates &victim)
{
    if (!((damaging.y < int(fieldHeight) && damaging.y >= 0) &&
          (damaging.x < int(fieldWidth) && damaging.x >= 0)) ||
          !field[damaging.y][damaging.x])
        return false;

    auto &victimObject  = field[victim.y][victim.x];
    auto damagingObject = field[damaging.y][damaging.x];

    size_t i = size_t(damaging.y);
    size_t j = size_t(damaging.x);
    int attackRange = int(gameField[i][j].obj->range());

    for (int _i = int(i) - 1; _i >= int(i) - attackRange; _i--)
    {
        if (_i < 0 || size_t(_i) >= height()) break;

        if (victim.y == _i && victim.x == int(j))
        {
            DamageMediator med;
            damagingObject->mediator = &med;

            med.setObject1(victimObject);
            med.setObject2(damagingObject);

            damagingObject->attack();

//            if (victimObject->health() <= 0)
//                delObject(victim);

            return true;
        }

        if (field[_i][j]) break;
    }

    for (int _i = int(i) + 1; _i <= int(i) + attackRange; _i++)
    {
        if (_i < 0 || size_t(_i) >= height()) break;

        if (victim.y == _i && victim.x == int(j))
        {
            DamageMediator med;
            damagingObject->mediator = &med;

            med.setObject1(victimObject);
            med.setObject2(damagingObject);

            damagingObject->attack();

//            if (victimObject->health() <= 0)
//                delObject(victim);

            return true;
        }

        if (field[_i][j]) break;
    }

    for (int _j = int(j) - 1; _j >= int(j) - attackRange; _j--)
    {
        if (_j < 0 || size_t(_j) >= height()) break;

        if (victim.y == int(i) && victim.x == _j)
        {
            DamageMediator med;
            damagingObject->mediator = &med;

            med.setObject1(victimObject);
            med.setObject2(damagingObject);

            damagingObject->attack();

//            if (victimObject->health() <= 0)
//                delObject(victim);

            return true;
        }

        if (field[i][_j]) break;
    }

    for (int _j = int(j) + 1; _j <= int(j) + attackRange; _j++)
    {
        if (_j < 0 || size_t(_j) >= width()) break;

        if (victim.y == int(i) && victim.x == _j)
        {
            DamageMediator med;
            damagingObject->mediator = &med;

            med.setObject1(victimObject);
            med.setObject2(damagingObject);

            damagingObject->attack();

//            if (victimObject->health() <= 0)
//                delObject(victim);

            return true;
        }

        if (field[i][_j]) break;
    }

    return false;
}

bool GameField::canMove(size_t i, size_t j) const
{
    bool result = false;

    if (i > 0)            result |= gameField[i-1][j].canStandUnit();
    if (j > 0)            result |= gameField[i][j-1].canStandUnit();
    if (i + 1 < height()) result |= gameField[i+1][j].canStandUnit();
    if (j + 1 < width())  result |= gameField[i][j+1].canStandUnit();

    return result;
}

bool GameField::canPlaceBuild(size_t i, size_t j) const
{
    if (!(i + 1 < height() && j + 1 < width())) return false;
    return gameField[i + 1][j].canPlaceBuild() &&
           gameField[i][j + 1].canPlaceBuild() &&
           gameField[i + 1][j + 1].canPlaceBuild() &&
           gameField[i][j].canPlaceBuild();
}

unsigned GameField::bases()
{
    return countBase;
}

GameCell& GameField::at(std::pair<size_t, size_t> coords)
{
    return (*this)[coords.first][coords.second];
}

const GameCell& GameField::at(std::pair<size_t, size_t> coords) const
{
    return gameField[coords.first][coords.second];
}

GameField::Intermediate::Intermediate(std::vector<GameCell>& vec) : vec(vec)
{}

GameCell& GameField::Intermediate::operator[](size_t j)
{
    return vec[j];
}

const GameCell& GameField::Intermediate::operator[](size_t j) const
{
    return vec[j];
}

GameField::Intermediate GameField::operator[](size_t i)
{
    return Intermediate(gameField[i]);
}
