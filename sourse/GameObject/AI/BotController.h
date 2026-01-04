#pragma once
#include <vector>
#include "../Card/Card.h"
#include "../Player/Player.h"
#include "../BattleSystem/BattleSystem.h"

class StateNewGame;

class BotController {
public:
    static void runTurn(
        Player* bot,
        Player* enemy,
        std::vector<std::unique_ptr<Card>>& hand,
        StateNewGame* state,
        BattleSystem* battle
    );
};
