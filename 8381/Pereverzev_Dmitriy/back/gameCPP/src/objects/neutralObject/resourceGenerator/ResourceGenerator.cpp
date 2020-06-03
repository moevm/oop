#include "ResourceGenerator.hpp"












ResourceGenerator::ResourceGenerator()
{
    resPerStep = 10;
    playerID = "empty";
    coefficient = 1;
}
ResourceGenerator::~ResourceGenerator()
{
    delete strategy;
}

bool ResourceGenerator::isMoveable()
{
    return false;
}

void ResourceGenerator::operator+(Object *object)
{
    if (this->playerID != object->getPlayerID())
    {
        this->playerID = object->getPlayerID();
        unsigned int objectType = object->getObjectType();
        
        if (objectType == ARCH_DPS || objectType == ARCH_TANK)
            setStrategy(new StrategyResArcher);
        if (objectType == CAV_DPS || objectType == CAV_TANK)
            setStrategy(new StrategyResCavalry);
        if (objectType == INF_DPS || objectType == INF_TANK)
            setStrategy(new StrategyResInfantry);

        useStrategy();
    }
    v8::Local<v8::Object> data = Nan::New<v8::Object>();
    if (!SetObjProperty(data, "type", resType))
        return;
    if (!SetObjProperty(data, "quantity", getResPerStepForUnit()))
        return;

    object->fireEvent("found resources", data);
}
void ResourceGenerator::setCoefficient(double coefficient) { this->coefficient = coefficient; }

void ResourceGenerator::setPlayerID(std::string playerID) { this->playerID = playerID; }

unsigned int ResourceGenerator::getResType() { return resType; }

double ResourceGenerator::getResPerStep() { return resPerStep; }

double ResourceGenerator::getCoefficient() { return coefficient; }

double ResourceGenerator::getResPerStepForUnit()
{
    double ret = resPerStep * coefficient;
    coefficient *= 1.1;
    return ret;
}

void ResourceGenerator::useStrategy() { coefficient = strategy->use(); }

void ResourceGenerator::setStrategy(Strategy *strategy) { this->strategy = strategy; }

v8::Local<v8::Object> ResourceGenerator::getFullInfo()
{
    v8::Local<v8::Object> info = NeutralObject::getFullInfo();

    SetObjProperty(info, "combatOrNeutral", "neutral");

    v8::Local<v8::Object> stats = Nan::New<v8::Object>();

    SetObjProperty(stats, "resType", resType);
    SetObjProperty(stats, "resPerStep", resPerStep);
    SetObjProperty(stats, "coefficient", coefficient);

    SetObjProperty(info, "stats", stats);

    return info;
}