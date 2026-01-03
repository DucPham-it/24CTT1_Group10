#include "NormalDamage.h"

void NormalDamage::apply(Player& target) {
    int dmgLeft = _amount;
    if (target.getShield() > 0) {
        int absorbed = min(dmgLeft, target.getShield());
        target.setShield(target.getShield() - absorbed);
        dmgLeft -= absorbed;
    }
    target.setHp(target.getHp() - dmgLeft);
}