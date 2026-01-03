#include "JackpotEffect.h"

JackpotEffect::JackpotEffect(int buffTurns, TickTrigger trigger)
    : StatusEffect(buffTurns + 1, trigger), // +1 lượt cooldown
      _buffTurns(buffTurns) {}

void JackpotEffect::onApply(Player& p, Damage* dmg) {
    int turnsLeft = _duration;

    // Nếu đã qua giai đoạn buff → chỉ còn cooldown
    if (turnsLeft <= 1) {
        cout << "[JACKPOT] Cooldown (no buff)\n";

        // thêm log để hiển thị ra giao diện 
        BattleLogService::push("[JACKPOT] Cooldown (no buff)\n");
        return;
    }

    // nếu được kích hoạt trong lượt 
    if (firstApply == true) {
        firstApply = false;

        // CHECK NERF CỦA URAUME
        if (p.isJackpotNerfed()) {
            cout << "[URAUME EFFECT] Jackpot bi nguyen rua! Chi hoi 500 HP!\n";

            // thêm log để hiển thị ra giao diện 
            BattleLogService::push("[URAUME EFFECT] Jackpot bi nguyen rua! Chi hoi 500 HP!\n");

            int newHp = min(Player::MAX_HP, p.getHp() + 500);
            p.setHp(newHp);
        } else {
            cout << "Ban duoc hoi day HP trong luot nay\n";

            // thêm log để hiển thị ra giao diện 
            BattleLogService::push("Ban duoc hoi day HP trong luot nay\n");

            p.setHp(Player::MAX_HP);
        }
        return;
    }

    // Buff các lượt sau
    if (p.isJackpotNerfed()) {
        int newHp = min(Player::MAX_HP, p.getHp() + 500);
        p.setHp(newHp);
        cout << "[URAUME EFFECT] Jackpot bi nguyen rua! Chi hoi 500 HP moi luot!\n";

        // thêm log để hiển thị ra giao diện 
        BattleLogService::push("[URAUME EFFECT] Jackpot bi nguyen rua! Chi hoi 500 HP moi luot!\n");
    } else {
        p.setHp(Player::MAX_HP);
        cout << "[JACKPOT] Hoi day HP moi luot\n";

        // thêm log để hiển thị ra giao diện 
        BattleLogService::push("[JACKPOT] Hoi day HP moi luot\n");
    }

    p.setAttackEnergy(Player::MAX_CURSED_ENERGY);
    p.setDefenseEnergy(0);
    p.setJackpotEnergy(0);
    cout << "[JACKPOT] auto attack energy\n";

    // thêm log để hiển thị ra giao diện 
    BattleLogService::push("[JACKPOT] auto attack energy\n");
}

bool JackpotEffect::hasTag(EffectTag tag) {
    return tag == EffectTag::Jackpot;
}
