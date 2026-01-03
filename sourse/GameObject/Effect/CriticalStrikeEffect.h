#pragma once 
#include "StatusEffect.h"

using namespace std;

class CriticalStrikeEffect : public StatusEffect {
private:
    float _chance;
    float _multiplier;

public:
    CriticalStrikeEffect(int turns, float c, float m, TickTrigger trigger);

    void onApply(Player&, Damage* damage = nullptr) override;
    bool hasTag(EffectTag tag) override;
};
