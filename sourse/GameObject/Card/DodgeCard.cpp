#include "DodgeCard.h"
#include "../../GameState/StateNewGame.h"
#include "../Effect/DodgeEffect.h"
#include "../../GameManager/SoundManager.h"

#include <iostream>
#include <format>

using namespace std;

DodgeCard::DodgeCard(float chance)
    : Card(format("Ne Tranh {}%", chance * 100), CardCategory::Defense),
      _dodgeChance(chance) {
    _iconPath = "attack_card.png";
}

void DodgeCard::execute(Player& self, Player&, StateNewGame& state) {

    cout << format("\n>>>> Su dung la bai: {} \n", _name);

    state.getScheduler().addEffect(
        &self,
        make_unique<DodgeEffect>(1, _dodgeChance, TickTrigger::endOfTurnOpponent),
        TriggerType::onBeforeReceiveDamage,
        1
    );
}

void DodgeCard::printDescription() const {
    cout << format("- {}% ne don.", _dodgeChance * 100) << endl;
}

unique_ptr<Card> DodgeCard::clone() const {
    return std::make_unique<DodgeCard>(*this);
}