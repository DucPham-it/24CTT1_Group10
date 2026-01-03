#include "DamageCard.h"
#include "../../GameState/StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"
#include "../Damage/NormalDamage.h"
#include "../../GameManager/SoundManager.h"
#include <iostream>
#include <format>

using namespace std;

DamageCard::DamageCard(int dmg)
    : Card(format("Tan Cong Thuong ({} dame)", dmg), CardCategory::Damage),
      _damageAmount(dmg) {
    _iconPath = "attack_card.png";
}

void DamageCard::execute(Player& self, Player& target, StateNewGame& state) {

    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    auto dmg = make_unique<NormalDamage>();
    dmg->setAmount(_damageAmount);

    state.getBattle()->attack(self, target, *dmg);
}

void DamageCard::printDescription() const {
    cout << format("- {} : Gay {} sat thuong co ban.", _name, _damageAmount) << endl;
}

unique_ptr<Card> DamageCard::clone() const {
    return std::make_unique<DamageCard>(*this);
}
