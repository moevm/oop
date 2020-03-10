#include "Attributes.h"

Attributes::Attributes(HpTypes health, RngTypes range, DmgTypes damage,
                       ArmTypes armor, ManaTypes mana) : health(unsigned(health)),
                                                         range (unsigned(range)),
                                                         damage(unsigned(damage)),
                                                         armor (unsigned(armor)),
                                                         mana  (unsigned(mana))
{}

Attributes::Attributes(unsigned health, unsigned range, unsigned damage,
                       unsigned armor, unsigned mana) : health(health),
                                                        range (range),
                                                        damage(damage),
                                                        armor (armor),
                                                        mana  (mana)
{}
