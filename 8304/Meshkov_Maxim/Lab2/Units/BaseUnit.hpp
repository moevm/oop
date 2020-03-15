#pragma once

#include "Unit.hpp"

class BaseUnit : public Unit {
public:
    int getHealth() const override {
        return m_health;
    }
    static const int maxHealth = 20;
    int getHit() const override {
        return m_hit;
    }
    bool icesWhenAttacks() const override {
        return m_icesWhenAttacks;
    }
    int getArmor() const override {
        return m_armor;
    }
    int getMoveRange() const override {
        return m_moveRange;
    }
    int getAttackRange() const override {
        return m_attackRange;
    }
    bool isIced() const override {
        return m_isIced;
    }

    void modifyHealth(int change) override;
    void ice() override;

    std::set<FieldPosition> findPossibleMoves(FieldPosition unitPosition, const Field &field) const override;
    std::set<FieldPosition> findPossibleAttacks(FieldPosition unitPosition, const Field &field) const override;

    void attack(FieldPosition victimPosition, Field &field) override;

protected:
    int m_health = maxHealth;

    int m_hit = 0;
    bool m_icesWhenAttacks = false;
    int m_armor = 0;
    int m_moveRange = 0;
    int m_attackRange = 0;
    bool m_isIced = false;

    BaseUnit &operator=(const BaseUnit &) = default;
};
