#include "Attributes.h"

Attributes::Attributes(HpTypes health, RngTypes range, DmgTypes damage,
                       ArmTypes armor, ManaTypes mana) : health(int(health)),
                                                         range (unsigned(range)),
                                                         damage(unsigned(damage)),
                                                         armor (unsigned(armor)),
                                                         mana  (unsigned(mana))
{}

Attributes::Attributes(int health, unsigned range, unsigned damage,
                       unsigned armor, unsigned mana) : health(health),
                                                        range (range),
                                                        damage(damage),
                                                        armor (armor),
                                                        mana  (mana)
{}

Attributes Attributes::operator+(const Attributes& attr)
{
    return Attributes(health + attr.health, range + attr.range, damage + attr.damage,
                      armor + attr.armor, mana + attr.mana);
}
