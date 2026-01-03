#include "DodgeEffect.h"


DodgeEffect::DodgeEffect(int turns, float c, TickTrigger trigger)
    : StatusEffect(turns, trigger), _chance(c) {}

void DodgeEffect::onApply(Player&, Damage* damage) {
    if (damage) {
        if (rand() % 100 < _chance * 100) {
            cout << "[CARD DODGE] Doi thu ne don thanh cong!\n";

            // thêm log để hiển thị ra giao diện 
            BattleEventQueue::instance().push("[CARD DODGE] Doi thu ne don thanh cong!\n");

            damage->setAmount(0);
        }
    }
}

bool DodgeEffect::hasTag(EffectTag tag) {
    return tag == EffectTag::Dodge;
}
