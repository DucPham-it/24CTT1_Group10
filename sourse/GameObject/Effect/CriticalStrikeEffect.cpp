#include "CriticalStrikeEffect.h"

CriticalStrikeEffect::CriticalStrikeEffect(int turns, float c, float m, TickTrigger trigger)
    : StatusEffect(turns, trigger), _chance(c), _multiplier(m) {}

void CriticalStrikeEffect::onApply(Player&, Damage* damage) {
    if (damage) {
        if (rand() % 100 < _chance * 100) {
            damage->setAmount(
                static_cast<int>(damage->getAmount() * _multiplier)
            );
            cout << "[CARD CRIT] Sat thuong chi mang(" 
                 << _chance * 100 << " %). Ban duoc x" 
                 << _multiplier << " damage\n";

            // thêm log để hiển thị ra giao diện 
            BattleEventQueue::instance().push(format("[CARD CRIT] Sat thuong chi mang ({} %). Ban duoc x{} damage\n",
                _chance * 100, _multiplier
            ));
        }
    }
}

bool CriticalStrikeEffect::hasTag(EffectTag tag) {
    return tag == EffectTag::CriticalStrike;
}
