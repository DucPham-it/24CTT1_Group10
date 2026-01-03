#pragma once

#include "StatusEffect.h"
using namespace std;
class StunEffect : public StatusEffect {
public:
    StunEffect(int turns, TickTrigger trigger);

    bool hasTag(EffectTag tag) override;
};
