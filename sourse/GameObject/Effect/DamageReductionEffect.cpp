#include "DamageReductionEffect.h"


DamageReductionEffect::DamageReductionEffect(int turns, float r, TickTrigger trigger)
    : StatusEffect(turns, trigger), _ratio(r) {}

void DamageReductionEffect::onApply(Player&, Damage* damage) {
    if (damage) {
        int reduced = static_cast<int>(damage->getAmount() * _ratio);
        damage->setAmount(damage->getAmount() - reduced);
        cout << "[CARD REDUCE DAMAGE] Doi thu giam " << _ratio * 100 << "% sat thuong\n";

        // thêm log để hiển thị ra giao diện 
        BattleEventQueue::instance().push(format("[REDUCE DAMAGE] Doi thu giam {}% sat thuong\n",
            _ratio * 100
        ));
    }
}

bool DamageReductionEffect::hasTag(EffectTag tag) {
    return tag == EffectTag::DamageReduction;
}
