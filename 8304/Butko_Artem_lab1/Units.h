#pragma once
#include <cmath>


class Position
{
public:
    Position() = default;
    Position(int x, int y)
    {
        position.first = x;
        position.second = y;
    }

    void setPosition(int x, int y)
    {
        position.first = x;
        position.second = y;
    }

    std::pair<int, int> getPosition()
    {
        return position;
    }

    ~Position() = default;

private:
    std::pair<int, int> position;
};

class HealthPoints
{
public:
    bool isDead;
    HealthPoints() = default;

    HealthPoints(int regen, int health)
    {
        this->healthRegen = regen;
        this->health = health;
        this->maxHealth = health;
        this->isDead = false;
    }

    void setHealth(int pHealth)
    {
        this->health = pHealth;
        this->maxHealth = health;
    }

    void setHealthRegen(int pHealthRegen)
    {
        this->healthRegen = pHealthRegen;
    }

    int getHealth()
    {
        return health;
    }

    int getHealthRegen()
    {
        return healthRegen;
    }

    void actDamaged(int damage)
    {
        health -= damage;
        if (health <= 0)
            isDead = true;
    }

    void actHealed(int heal)
    {
        if (health + heal <= maxHealth)
            health += heal;
        else
            health = maxHealth;
    }
    ~HealthPoints() = default;


private:
    int healthRegen;
    int health;
    int maxHealth;
};

class StaminaPoints
{
public:
    StaminaPoints() = default;

    StaminaPoints(int regen, int stamina) : staminaRegen(regen), stamina(stamina) {}

    void setStamina(int pStamina)
    {
        this->stamina = pStamina;
    }

    void setStaminaRegen(int pStaminaRegen)
    {
        this->staminaRegen = pStaminaRegen;
    }

    int getStamina()
    {
        return stamina;
    }

    int getHealthRegen()
    {
        return staminaRegen;
    }

    ~StaminaPoints() = default;

private:
    int staminaRegen;
    int stamina;

};

class DamagePoints
{
public:
    DamagePoints() = default;

    DamagePoints(int damage, int range)
    {
        this->damage.first = damage;
        this->damage.second = range;
    }

    void setDamage(int pDamage, int range)
    {
        this->damage.first = pDamage;
        this->damage.second = range;
    }

    std::pair<int, int> getDamage()
    {
        return damage;
    }

    int getDamagePoints()
    {
        return damage.first;
    }

    int getDamageRange()
    {
        return damage.second;
    }

    ~DamagePoints() = default;

private:
    std::pair<int, int> damage;
};

class Level
{
public:
    Level() = default;
    ~Level() = default;

    void levelUp()
    {
        level++;
    }

    int getlevel()
    {
        return level;
    }

private:
    int level;
};

class Unit
{
public:
    virtual void move(int x, int y) = 0;
    virtual void attack(std::shared_ptr<Unit> target) = 0;

    HealthPoints health{};
    StaminaPoints stamina{};
    DamagePoints damage;
    Position position;
    Level level{};
    std::string name;
};

class Warrior : public Unit
{
public:
    Warrior(int health, int stamina, int damage)
    {
        this->health.setHealth(health);
        this->stamina.setStamina(stamina);
        this->damage.setDamage(damage, 1);
        this->name = "Warrior";
    }

    void move(int x, int y) override
    {
        /* будет зависеть от тайла на который переместится */
        position.setPosition(position.getPosition().first + x, position.getPosition().second + y);
    }

    void attack(std::shared_ptr<Unit> target) override
    {
        if (sqrt(std::pow(abs(this->position.getPosition().first - target->position.getPosition().first), 2)
                 + std::pow(abs(this->position.getPosition().second - target->position.getPosition().second), 2)) <= this->damage.getDamageRange())
            target->health.actDamaged(this->damage.getDamagePoints());
        if (target->health.isDead)
        {
            std::cout << target->name << " is dead." << std::endl;
            this->level.levelUp();
        }
    }
    ~Warrior() = default;
};

class Samurai : public Warrior
{
public:
    Samurai() : Warrior(200, 200, 50) {};
    ~Samurai() = default;
};

class Ninja : public Warrior
{
public:
    Ninja() : Warrior(150, 150, 70) {};
    ~Ninja() = default;
};

class Archer : public Unit
{
public:
    Archer(int health, int stamina, int damage)
    {
        this->health.setHealth(health);
        this->stamina.setStamina(stamina);
        this->damage.setDamage(damage, 3);
        this->name = "Archer";
    }

    void move(int x, int y) override
    {
        /* будет зависеть от тайла на который переместится */
        position.setPosition(position.getPosition().first + x, position.getPosition().second + y);
    }

    void attack(std::shared_ptr<Unit> target) override
    {
        if (sqrt(std::pow(abs(this->position.getPosition().first - target->position.getPosition().first), 2)
                 + std::pow(abs(this->position.getPosition().second - target->position.getPosition().second), 2)) <= this->damage.getDamageRange())
            target->health.actDamaged(this->damage.getDamagePoints());
        if (target->health.isDead)
        {
            std::cout << target->name << " is dead." << std::endl;
            this->level.levelUp();
        }
    }
    ~Archer()  = default;
};

class Gunner : public Archer
{
public:
    Gunner() : Archer(100, 200, 80) {};
    ~Gunner() = default;
};

class Crossbowman : public Archer
{
public:
    Crossbowman() : Archer(120, 180, 70) {};
    ~Crossbowman() = default;
};

class Mage : public Unit
{
public:
    Mage(int health, int stamina, int damage)
    {
        this->health.setHealth(health);
        this->stamina.setStamina(stamina);
        this->damage.setDamage(damage, 2);
        this->name = "Mage";
    }

    void move(int x, int y) override
    {
        /* будет зависеть от тайла на который переместится */
        position.setPosition(position.getPosition().first + x, position.getPosition().second + y);
    }

    void attack(std::shared_ptr<Unit> target) override
    {
        if (sqrt(std::pow(abs(this->position.getPosition().first - target->position.getPosition().first), 2)
                 + std::pow(abs(this->position.getPosition().second - target->position.getPosition().second), 2)) <= this->damage.getDamageRange())
            target->health.actDamaged(this->damage.getDamagePoints());
        if (target->health.isDead)
        {
            std::cout << target->name << " is dead." << std::endl;
            this->level.levelUp();
        }
    }
    ~Mage() = default;
};

class Spirit : public Mage
{
public:
    Spirit() : Mage(60, 200, 110) {};
    ~Spirit()  = default;
};

class Monk : public Mage
{
public:
    Monk() : Mage(100, 180, 80) {};
    ~Monk() = default;
};