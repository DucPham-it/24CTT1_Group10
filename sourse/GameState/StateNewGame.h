#pragma once

#include "State.h"

#include "../GameObject/BattleSystem/BattleSystem.h"
#include "../GameObject/Deck/Deck.h"
#include "../GameObject/Player/Player.h"
#include "../GameObject/Card/Card.h"

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
    // TURN MESSAGE
    // =========================
    struct TurnLog {
        int turn;
        vector<std::string> lines;
    };

    deque<TurnLog> _turnLogs;

    void collectBattleEvents();
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
        BotAct,      // Lượt của bot
    };
    Phase _phase;

    // =========================
    // INPUT BOX (ENERGY)
    // =========================
    struct InputBox {
        RectangleShape box;
        Text text;
        string value;
        bool active = false;

        void handleEvent(Event& e);
        int  getInt() const;
        void clear();
    };

    Text txtAtkLabel;
    Text txtDefLabel;
    Text txtJpLabel;

    Text txtEnergyHint;

    InputBox atkBox;
    InputBox defBox;
    InputBox jpBox;
    
    RectangleShape btnConfirmEnergy;
    Text txtConfirmEnergy;
    int _energyFocus = 0;

    void updateEnergyFocus();

    // =========================
    // CARD PICK UI
    // =========================
    struct CardUI {
        int index;
        bool selected;
        Sprite sprite;
        Vector2f basePos;
    };

    vector<unique_ptr<Card>> _hand;
    vector<CardUI> m_HandUI;
    vector<int> _picked;

    Vector2f handOrigin;
    float handSpacing;

    RectangleShape btnConfirmCards;
    Text txtConfirmCards;

    // ===== BOT SELECT UI =====
    RectangleShape panelBot;
    vector<RectangleShape> botButtons;   
    vector<Text> botTexts;               

    // =======================
    // PLAYED CARDS (LAST TURN)
    // =======================
    vector<unique_ptr<Card>> _playedP1;
    vector<unique_ptr<Card>> _playedP2;

    vector<Sprite> _playedP1UI;
    vector<Sprite> _playedP2UI;

    Text txtPlayedP1;
    Text txtPlayedP2;

    void savePlayedCards(Player* owner, vector<int>& picked);

    // =========================
    // HUD / UI
    // =========================
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

    void handleEnergyConfirm();
    void handleCardClick(Vector2f mouse);
    void handleCardConfirm();

    void swapTurns();
    void endTurn();
    void processEndOfTurn();

    
};
