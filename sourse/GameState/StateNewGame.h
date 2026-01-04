#pragma once

#include "State.h"

#include "../GameObject/BattleSystem/BattleSystem.h"
#include "../GameObject/Deck/Deck.h"
#include "../GameObject/Player/Player.h"
#include "../GameObject/Card/Card.h"

#include "../UI/EnergyInputUI.h"
#include "../UI/HandUI.h"
#include "../UI/PlayedCardsView.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <deque>

using namespace sf;
using namespace std;

class StateNewGame : public State {
public:
    // =========================
    // CTOR / DTOR
    // =========================
    StateNewGame();
    ~StateNewGame();

    // ===== GAME MODE =====
    static void setAIMode(bool isAI);
    static bool isAIMode();

    // =========================
    // STATE OVERRIDE
    // =========================
    void Init() override;
    void Handle(Event event) override;
    void Render(RenderWindow* window) override;

    void Exit() override;
    void Pause() override;
    void Resume() override;

    // =========================
    // GETTERS
    // =========================
    EffectScheduler& getScheduler();
    BattleSystem* getBattle();

    // =========================
    // STATUS MESSAGE
    // =========================
    struct StatusMessage {
        std::string text;
        float lifetime;
    };
    void pushStatusText(const std::string& text);
    // =========================
    // API cho BotController
    // =========================
    void recordPlayedCards(Player* owner, std::vector<int>& picked);
private:
    // =========================
    // CORE GAME OBJECTS
    // =========================
    unique_ptr<Player> _player1;
    unique_ptr<Player> _player2;

    Player* _current;
    Player* _opponent;

    unique_ptr<Deck> _deck;
    BattleSystem* _battle;
    EffectScheduler _scheduler;

    bool _isGameOver;
    bool _isWinGame;
    int  _turnCount;

    static bool s_IsAIMode;
    bool _waitForNextTurn;

    // =========================
    // SOUND 
    // =========================
    bool _combatMusicStarted = false;

    // =========================
    // TURN PHASE
    // =========================
    enum class Phase {
        SelectBot,   // chọn chế độ trước khi chơi
        None,         // bắt đầu lượt
        InputEnergy,  // nhập chú lực
        PickCards,   // chọn bài
        BotAct      // Lượt của bot
    };
    Phase _phase;

    // =========================
    // INPUT BOX (ENERGY)
    // =========================
    
    EnergyInputUI _energyUI;
    Text txtEnergyHint;
    Text txtConfirmEnergy;

    // =========================
    // CARD PICK UI
    // =========================
    vector<unique_ptr<Card>> _hand;
    HandUI _handUI;
    // ===== BOT SELECT UI =====
    RectangleShape panelBot;
    vector<RectangleShape> botButtons;   
    vector<Text> botTexts;               

    // ===== STATUS TEXT QUEUE =====
    deque<StatusMessage> _statusQueue;
    sf::Clock _statusClock;      
    float _lastStatusTime = 0.f;
    const float STATUS_DURATION = 6.f;

    // =======================
    // PLAYED CARDS (LAST TURN)
    // =======================

    PlayedCardsView _playedView;

    // =========================
    // HUD / UI
    // =========================
    float DESIGN_W;
    float DESIGN_H;

    float sx;
    float sy;
    Font* _font;
    Sprite m_Background;
    Sprite avatarP1;
    Sprite avatarP2;

    RectangleShape panelP1;
    RectangleShape panelP2;

    Text txtTurn;

    Text txtP1_HP;
    Text txtP1_Rage;
    Text txtP1_Shield;

    Text txtP2_HP;
    Text txtP2_Rage;
    Text txtP2_Shield;


    Sprite _gameOverSprite;
    Texture* _gameOverTexture = nullptr;

    IntRect _gameOverRect;
    Clock _gameOverClock;

    // ===== GAME OVER =====
    int _gameOverFrame = 0;
    const int GAME_OVER_FRAME_COUNT = 12;
    const float GAME_OVER_FRAME_TIME = 0.1f;

    bool _showGameOver = false;
    // =========================
    // CORE LOGIC
    // =========================
    void handleBotSelect(Vector2f mouse);
    void handleBotTurn();

    void drawHand();

    void swapTurns();
    void endTurn();
    void processEndOfTurn();

    
};
