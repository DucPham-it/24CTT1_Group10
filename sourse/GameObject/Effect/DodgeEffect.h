#pragma once 
#include "StatusEffect.h"

using namespace std;

class DodgeEffect : public StatusEffect {
private:
    float _chance;

public:
    DodgeEffect(int turns, float c, TickTrigger trigger);

    void onApply(Player&, Damage* damage = nullptr) override;
    bool hasTag(EffectTag tag) override;
};
