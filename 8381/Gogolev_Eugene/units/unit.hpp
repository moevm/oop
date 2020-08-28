#ifndef GOGOLEV_STRATEGY_UNIT_HPP
#define GOGOLEV_STRATEGY_UNIT_HPP

#include "../stl.hpp"
#include "../enums.hpp"
#include "../loggers/logger.hpp"

class Tile;

class Unit {
public:
    class GameHandler {
    public:
        virtual bool onField(int x, int y) = 0;
        virtual Tile* getTile(int x, int y) = 0;
        virtual Unit* createUnit(string key) = 0;
        virtual const vector<Unit*> * findUnits(int x, int y, int radius) = 0;
        virtual Unit* findUnit(int id) = 0;
        virtual int getSizeX () const = 0;
        virtual int getSizeY () const = 0;
        virtual Logger& getLogger () = 0;
    };

public:
    Unit();
    virtual ~Unit();

    bool isDead() const;
    void validateChar(int x, int y);
    virtual char getChar(int x, int y);
    virtual MovingType getMovingType();

    void setTeam(Team team);
    Team getTeam();

    int getId() const;
    int getX() const;
    int getY() const;
    virtual void setXY(int x, int y);

    int sqrDistanceTo(int x, int y) const;

    int getTargetX() const;
    int getTargetY() const;
    void setTargetXY(int x, int y);

    virtual void onGameFieldEnter(int id, GameHandler *game);
    virtual void update();
    virtual void spotted(Unit* other);
    void operator<(Unit* other);

    virtual const string& getType() = 0;

    virtual void save(ostream &os);
    virtual void load(istream &is);

protected:
    // Non serializable
    GameHandler *gameHandler;
    int id = -1;
    // Serializable
    Team team;
    int x;
    int y;
    int targetX;
    int targetY;
    int targetUnitId = -1;
    int hp;

    virtual int getMaxHP();
    virtual int attackDistance();
    virtual int visionDistance();
    virtual int getSpeed();
    virtual DamageType getDamageType();
    virtual int getDamage();
    virtual void takeDamage(DamageType damageType, int value);

    bool isAttackable(Unit *other);
    void dealDamage(Unit *other);
    void operator*(Unit* other);

private:
    bool moveTo(int x, int y);
    bool stepTo(int x, int y);
    bool walkTo(int x, int y);
};



#endif //GOGOLEV_STRATEGY_UNIT_HPP
