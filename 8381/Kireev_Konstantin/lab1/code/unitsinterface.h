#pragma once
#include <field.h>
#include <cellInterface.h>

class UnitInterface : public cellInterface
{
protected:
    //характеристики юнита
    int health;
    int armor;
    int damage;
public:
    bool isMove() const override; //возвращает true, если объект можно передвигать

    int getHealth() const; //получить количество здоровья
    void setHealth(int healthNewValue); //установить количество здоровья

    int getArmor() const; //получить количество брони
    void setArmor(int armorNewValue); //установить количество брони

    int getDamage() const; //получить количество урона
    void setDamage(int damageNewValue); //установить количество урона

    void setAllAttribues(int health, int armor, int damage); //устанавливает все характеристики юнита
};

class InfantryInterface : public UnitInterface //интерфейс пехоты
{
};

class ArcherInterface : public UnitInterface //интерфецс лучников
{
};

class CavalryInterface : public UnitInterface //интерфейс конницы
{
};

class UnitCritInterface : printInterface //интерфейс для юнитов с критическим уроном
{
protected:
    double critFactor;
};

class UnitDamageAbsorberInterface : printInterface //интерфейс для юнитов с поглощением урона
{
protected:
    double absorptionFactor;
};
