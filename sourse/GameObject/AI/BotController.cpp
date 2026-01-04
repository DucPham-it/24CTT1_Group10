#include "BotController.h"
#include "../../GameState/StateNewGame.h"
using namespace std;
void BotController::runTurn(
    Player* bot,
    Player* enemy,
    std::vector<std::unique_ptr<Card>>& hand,
    StateNewGame* state,
    BattleSystem* battle
){
    bot->allocateCursedEnergy();

    auto cards = bot->pickCards(hand);

    std::vector<int> picked;
    for (auto c : cards) {
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].get() == c) {
                picked.push_back(i);
                break;
            }
        }
    }

    state->recordPlayedCards(bot, picked);

    for (auto c : cards)
        c->execute(*bot, *enemy, *state);

    battle->onTurnEnd(*bot);
}
