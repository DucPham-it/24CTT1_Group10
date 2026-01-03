#include "DoubleJackpotRollCard.h"
#include "../../GameState/StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"
#include "../../GameManager/SoundManager.h"

#include <iostream>
#include <format>

using namespace std;

DoubleJackpotRollCard::DoubleJackpotRollCard()
    : Card("Quay Jackpot (2 lan)", CardCategory::Effect) {
    _iconPath = "double_jackpot_card.png";
}

void DoubleJackpotRollCard::execute(Player& self, Player& target, StateNewGame& state) {


    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    state.getBattle()->rollJackpot(self, target, 2);
}

void DoubleJackpotRollCard::printDescription() const {
    cout << "- Quay Jackpot 2 lan.\n";
}

unique_ptr<Card> DoubleJackpotRollCard::clone() const {
    return std::make_unique<DoubleJackpotRollCard>(*this);
}
