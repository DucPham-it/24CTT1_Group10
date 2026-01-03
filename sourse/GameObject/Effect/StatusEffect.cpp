#include "StatusEffect.h"

StatusEffect::StatusEffect(int turns, TickTrigger tickAt)
    : _duration(turns), _tickTrigger(tickAt)
{
}

StatusEffect::~StatusEffect() = default;

TickTrigger StatusEffect::getTickTrigger() const {
    return _tickTrigger;
}

bool StatusEffect::hasTag(EffectTag) {
    return false;
}

void StatusEffect::onApply(Player&, Damage*) {
    // default: không làm gì
}

void StatusEffect::tick() {
    _duration--;
}

bool StatusEffect::isExpired() const {
    return _duration <= 0;
}
