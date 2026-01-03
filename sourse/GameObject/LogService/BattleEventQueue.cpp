#include "BattleEventQueue.h"

BattleEventQueue& BattleEventQueue::instance() {
        static BattleEventQueue q;
        return q;
    }

void BattleEventQueue::push(const std::string& msg) {
        _events.push_back({ msg });
    }

bool BattleEventQueue::empty() const {
        return _events.empty();
    }

BattleEvent BattleEventQueue::pop() {
        BattleEvent e = _events.front();
        _events.pop_front();
        return e;
    }