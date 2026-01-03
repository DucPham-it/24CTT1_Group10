#include "PiercingDamage.h"

void PiercingDamage::apply(Player& target) {
    target.setHp(target.getHp() - _amount);
}