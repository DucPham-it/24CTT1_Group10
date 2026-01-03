#include "StunEffect.h"

StunEffect::StunEffect(int turns, TickTrigger trigger)
    : StatusEffect(turns, trigger)
{
}

bool StunEffect::hasTag(EffectTag tag)
{
    return tag == EffectTag::Stun;
}
