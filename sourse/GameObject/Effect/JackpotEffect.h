#pragma once
#include "StatusEffect.h"
#include "../Player/Player.h"

using namespace std;

class JackpotEffect : public StatusEffect {
private:
    int _buffTurns;   // số lượt có buff thật sự : 5, duration = 5 + 1 = 6
    bool firstApply = true;

public:
    JackpotEffect(int buffTurns, TickTrigger trigger);

    void onApply(Player& p, Damage* dmg = nullptr) override;
    bool hasTag(EffectTag tag) override;
};
