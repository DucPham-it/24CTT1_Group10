#include "EffectScheduler.h"

using namespace std;

vector<ScheduledEffect>& EffectScheduler::getScheduledEffects() {
    return _scheduledEffects;
}

void EffectScheduler::setScheduledEffects(ScheduledEffect scheduledEffect) {
    _scheduledEffects.push_back(move(scheduledEffect));
}

void EffectScheduler::addEffect(
    Player* target,
    unique_ptr<StatusEffect> eff,
    TriggerType trigger,
    int duration
) {
    setScheduledEffects({ target, move(eff), trigger, duration });
}

// gọi khi event xảy ra
void EffectScheduler::processTrigger(
    TriggerType trigger,
    Player& currentPlayer,
    Damage* damage
) {
    for (auto it = _scheduledEffects.begin(); it != _scheduledEffects.end();) {
        if (it->trigger == trigger && it->target == &currentPlayer) {
            it->effect->onApply(*it->target, damage);
        }
        ++it;
    }
}

bool EffectScheduler::hasEffect(Player* target, EffectTag tag) {
    for (const auto& se : _scheduledEffects) {
        if (se.target == target && se.effect->hasTag(tag)) {
            return true;
        }
    }
    return false;
}

void EffectScheduler::tickPlayer(Player& p) {
    for (auto it = _scheduledEffects.begin(); it != _scheduledEffects.end();) {
        if (it->target == &p) {
            it->effect->tick();

            if (it->effect->isExpired()) {
                it = _scheduledEffects.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void EffectScheduler::tickByTrigger(TickTrigger trigger, Player& target) {
    for (auto it = _scheduledEffects.begin(); it != _scheduledEffects.end();) {
        if (it->effect->getTickTrigger() == trigger && it->target == &target) {
            it->effect->tick();
        }

        if (it->effect->isExpired()) {
            it = _scheduledEffects.erase(it);
        } else {
            ++it;
        }
    }
}
