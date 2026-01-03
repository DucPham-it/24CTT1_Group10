
#include "BattleLogService.h"
#include "../../GameState/StateNewGame.h"

StateNewGame* BattleLogService::_state = nullptr;

void BattleLogService::bind(StateNewGame* state) {
    _state = state;
}

void BattleLogService::push(const string& text) {
    if (_state)
        _state->pushStatusText(text);
}
