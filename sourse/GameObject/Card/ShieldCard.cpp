#include "ShieldCard.h"
#include "../Player/Player.h"
#include "../../GameState/StateNewGame.h"
#include "../../GameManager/SoundManager.h"

#include <iostream>
#include <format>

ShieldCard::ShieldCard(int shield)
    : Card(format("Phong Thu Thuong (+{} shield)", shield), CardCategory::Defense),
      _shieldAmount(shield) {
    _iconPath = "shield_card.png";
}

void ShieldCard::execute(Player& self, Player&, StateNewGame& state) {

    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    self.addShield(_shieldAmount);
}

void ShieldCard::printDescription() const {
    cout << format("- Tang {} shield.", _shieldAmount) << endl;
}

unique_ptr<Card> ShieldCard::clone() const {
    return std::make_unique<ShieldCard>(*this);
}