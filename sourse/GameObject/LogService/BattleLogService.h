
#pragma once
#include <string>
class StateNewGame;

using namespace std;

class BattleLogService {
public:
    static void bind(StateNewGame* state);
    static void push(const string& text);

private:
    static StateNewGame* _state;
};
