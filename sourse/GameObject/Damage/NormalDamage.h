#pragma once
#include "Damage.h"
#include "../Player/Player.h"

class NormalDamage : public Damage {
public:
    void apply(Player& target) override ;
};


