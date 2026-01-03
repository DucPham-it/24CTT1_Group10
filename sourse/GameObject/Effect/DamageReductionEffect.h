#pragma once 
#include "StatusEffect.h"

using namespace std;

class DamageReductionEffect : public StatusEffect {
private:
    float _ratio;

public:
    DamageReductionEffect(int turns, float r, TickTrigger trigger);

    void onApply(Player&, Damage* damage = nullptr) override;
    bool hasTag(EffectTag tag) override;
};
