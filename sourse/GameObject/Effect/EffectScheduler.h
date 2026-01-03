#pragma once
class Player;
#include "StatusEffect.h"
#include "ScheduledEffect.h"
#include <vector>
#include <memory>

class EffectScheduler {
private:
    std::vector<ScheduledEffect> _scheduledEffects;

public:
    std::vector<ScheduledEffect>& getScheduledEffects();
    void setScheduledEffects(ScheduledEffect scheduledEffect);

public:
    void addEffect(Player* target, std::unique_ptr<StatusEffect> eff, TriggerType trigger, int duration);

    // gọi khi event xảy ra
    void processTrigger(TriggerType trigger, Player& currentPlayer, Damage* damage = nullptr);

    bool hasEffect(Player* target, EffectTag tag);

    void tickPlayer(Player& p);
    void tickByTrigger(TickTrigger trigger, Player& target);
};
