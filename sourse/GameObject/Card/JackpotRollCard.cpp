#include "JackpotRollCard.h"
#include "../../GameState/StateNewGame.h"
#include "../BattleSystem/BattleSystem.h"
#include "../../GameManager/SoundManager.h"

#include <iostream>
#include <format>

using namespace std;

JackpotRollCard::JackpotRollCard()
    : Card("Quay Jackpot (1 lan)", CardCategory::Effect) {
    _iconPath = "jackpot_card.png";
}

void JackpotRollCard::execute(Player& self, Player& target, StateNewGame& state) {

    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    state.getBattle()->rollJackpot(self, target, 1);
}

void JackpotRollCard::printDescription() const {
    cout << "- Quay Jackpot 1 lan.\n";
    BattleEventQueue::instance().push(format("- Quay Jackpot 1 lan."));
}

unique_ptr<Card> JackpotRollCard::clone() const {
    return std::make_unique<JackpotRollCard>(*this);
}
