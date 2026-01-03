#pragma once

#include "../Damage/Damage.h"
#include "../LogService/BattleLogService.h"
#include <format>
#include <iostream>

class Player;

using namespace std;

enum class TickTrigger {
    none,
    endOfTurn,
    afterReceiveDamage,
    beforeReceiveDamage,
    endOfTurnOpponent
};

enum class EffectTag {
    Jackpot,
    Stun,
    Dodge,
    DamageReduction,
    CriticalStrike
};

// ===== CLASS =====
class StatusEffect {
protected:
    int _duration;
    TickTrigger _tickTrigger; // thời điểm giảm duration

public:
    explicit StatusEffect(int turns, TickTrigger tickAt);
    virtual ~StatusEffect();

    // ===== GET =====
    TickTrigger getTickTrigger() const;

    // ===== QUERY =====
    virtual bool hasTag(EffectTag);

    // ===== LIFECYCLE =====
    virtual void onApply(Player&, Damage* dmg = nullptr);

    virtual void tick();
    bool isExpired() const;
};
