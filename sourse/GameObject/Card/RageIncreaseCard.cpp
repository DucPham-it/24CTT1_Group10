#include "RageIncreaseCard.h"
#include "../Player/Player.h"
#include "../../GameState/StateNewGame.h"
#include "../../GameManager/SoundManager.h"

#include <iostream>
#include <format>

using namespace std;

RageIncreaseCard::RageIncreaseCard(int increase)
    : Card(format("Tang {} diem No II", increase), CardCategory::Effect),
      _rageIncrease(increase) {
    _iconPath = "pow_card.png";
}

void RageIncreaseCard::execute(Player& self, Player&, StateNewGame& state) {

    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    self.increaseRage(_rageIncrease);
}

void RageIncreaseCard::printDescription() const {
    cout << format("- Tang {} diem no II.", _rageIncrease) << endl;
}

unique_ptr<Card> RageIncreaseCard::clone() const {
    return std::make_unique<RageIncreaseCard>(*this);
}