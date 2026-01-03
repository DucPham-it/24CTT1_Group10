#pragma once
#include <deque>
#include <string>

struct BattleEvent {
    std::string text;
};

class BattleEventQueue {
public:
    static BattleEventQueue& instance();
    void push(const std::string& msg);
    bool empty() const;
    BattleEvent pop();

private:
    std::deque<BattleEvent> _events;
};
