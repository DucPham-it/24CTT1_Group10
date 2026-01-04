#include "StateNewGame.h"

#include "../GameManager/StateManager.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/WindowManager.h"
#include "../GameManager/SoundManager.h"

#include "../GameObject/NewGameConfig/GameConfig.h"
#include "../GameObject/BattleSystem/BattleSystem.h"
#include "../GameObject/Card/Card.h"
#include "../GameObject/LogService/BattleLogService.h"
#include "../GameObject/AI/BotController.h"
// ===== AI =====
#include "../GameObject/AI/BotPlayer.h"
#include "../GameObject/AI/BotHakari.h"
#include "../GameObject/AI/CharlesBoss.h"
#include "../GameObject/AI/KashimoBoss.h"
#include "../GameObject/AI/UraumeBoss.h"
#include "../GameObject/AI/BotController.h"

using namespace sf;
using namespace std;

// =====================================================
// STATIC GAME MODE
// =====================================================
bool StateNewGame::s_IsAIMode = false;

void StateNewGame::setAIMode(bool isAI) {
    s_IsAIMode = isAI;
}

bool StateNewGame::isAIMode() {
    return s_IsAIMode;
}

// =====================================================
// CTOR / DTOR
// =====================================================
StateNewGame::StateNewGame()
    : _battle(nullptr),
    _current(nullptr),
    _opponent(nullptr),
    _isGameOver(false),
    _isWinGame(false),
    _turnCount(1),
    _phase(Phase::None),
    _font(nullptr)
{
    _battle = new BattleSystem(_scheduler);
    BattleLogService::bind(this); // class dùng để ghi log
}

StateNewGame::~StateNewGame() {
    delete _battle;
}

// =====================================================
// OVERRIDE STATE
// =====================================================
void StateNewGame::Exit() {
}
void StateNewGame::Pause() {}
void StateNewGame::Resume() {}

// =====================================================
// GETTERS
// =====================================================

EffectScheduler& StateNewGame::getScheduler() { return _scheduler; }
BattleSystem* StateNewGame::getBattle() { return _battle; }


// =====================================================
// INIT
// =====================================================
void StateNewGame::Init()
{
    // ================== DESIGN RESOLUTION ==================
    sx = WM_GI->getScaleX();
    sy = WM_GI->getScaleY();
    float DESIGN_W = 1366.f;
    float DESIGN_H = 768.f;

    float W = WM_GI->getWidthScreen();
    float H = WM_GI->getHeightScreen();

    // ================== SYSTEM ==================
    RM_GI->getBackgroundMusic()->stop();
    SoundManager::instance().stopMusic();

    GameConfig::instance().loadFromFile("GameConfig/game_config.txt");
    Player::loadConfig();

    _font = RM_GI->getFont("Minecraft.ttf");

    // ================== BACKGROUND ==================
    if (auto bg = RM_GI->getTexture("battle_bg.png")) {
        m_Background.setTexture(*bg);
        m_Background.setScale(
            W / bg->getSize().x,
            H / bg->getSize().y
        );
    }

    // ================== GAME OVER ==================
    _gameOverTexture = RM_GI->getTexture("gameOver-animation.png");
    if (_gameOverTexture) {
        _gameOverRect = sf::IntRect(0, 0, 94, 13);
        _gameOverSprite.setTexture(*_gameOverTexture);
        _gameOverSprite.setTextureRect(_gameOverRect);
        _gameOverSprite.setScale(10.f * sx, 10.f * sy);
        _gameOverSprite.setOrigin(40.f, 8.f);
        _gameOverSprite.setPosition(W / 2.f, H / 2.f);
    }

    // ================== BOT SELECT ==================
    panelBot.setSize({ 450 * sx, 300 * sy });
    panelBot.setPosition(
        (DESIGN_W / 2 - 230) * sx,
        (DESIGN_H / 2 - 140) * sy
    );
    panelBot.setFillColor(Color(0, 0, 0, 210));

    vector<string> botNames = {
        "Hakari (Jackpot)",
        "Charles Bernard (Dodge)",
        "Kashimo Hajime (Burst)",
        "Uraume (Freeze)"
    };

    botButtons.clear();
    botTexts.clear();

    for (int i = 0; i < 4; ++i) {
        RectangleShape btn;
        btn.setSize({ 330 * sx, 42 * sy });
        btn.setPosition(
            (DESIGN_W / 2 - 160) * sx,
            (DESIGN_H / 2 - 80 + i * 48) * sy
        );
        btn.setFillColor(Color(120, 120, 180));
        botButtons.push_back(btn);

        Text t;
        t.setFont(*_font);
        t.setCharacterSize(static_cast<unsigned>(19 * sy));
        t.setString(botNames[i]);
        t.setPosition(
            btn.getPosition().x + 16 * sx,
            btn.getPosition().y + 8 * sy
        );
        botTexts.push_back(t);
    }

    // ================== HUD PANELS ==================
    panelP1.setSize({ 180 * sx,100* sy });
    panelP1.setPosition({ 20 * sx, (DESIGN_H - 100) * sy });
    panelP1.setFillColor(Color(0, 0, 0, 150));

    panelP2.setSize({ 180 * sx,100 * sy });
    panelP2.setPosition({ (DESIGN_W - 220) * sx, 20 * sy });
    panelP2.setFillColor(Color(0, 0, 0, 150));

    auto setupText = [&](Text& t, float x, float y, Color c) {
        t.setFont(*_font);
        t.setCharacterSize(static_cast<unsigned>(20 * sy));
        t.setFillColor(c);
        t.setPosition(x * sx, y * sy);
    };

    setupText(txtP1_HP, 40, DESIGN_H - 90, Color::Red);
    setupText(txtP1_Rage, 40, DESIGN_H - 70, Color::Yellow);
    setupText(txtP1_Shield, 40, DESIGN_H - 50, Color::Cyan);

    setupText(txtP2_HP, DESIGN_W - 200, 30, Color::Red);
    setupText(txtP2_Rage, DESIGN_W - 200, 50, Color::Yellow);
    setupText(txtP2_Shield, DESIGN_W - 200, 70, Color::Cyan);

    txtTurn.setFont(*_font);
    txtTurn.setCharacterSize(static_cast<unsigned>(24 * sy));
    txtTurn.setPosition((DESIGN_W / 2 - 90) * sx, 10 * sy);

    // ================== AVATAR ==================
    if (auto tex = RM_GI->getTexture("p1.png")) {
        avatarP1.setTexture(*tex);
        float scale = (35.f / tex->getSize().y) * sy;
        avatarP1.setScale(scale, scale);
        avatarP1.setPosition(
            panelP1.getPosition().x + panelP1.getSize().x + 20 * sx,
            panelP1.getPosition().y + panelP1.getSize().y / 2 -
            avatarP1.getGlobalBounds().height / 2
        );
    }

    if (auto tex = RM_GI->getTexture("p2.png")) {
        avatarP2.setTexture(*tex);
        float scale = (35.f / tex->getSize().y) * sy;
        avatarP2.setScale(scale, scale);
        avatarP2.setPosition(
            panelP2.getPosition().x - avatarP2.getGlobalBounds().width - 20 * sx,
            panelP2.getPosition().y + panelP2.getSize().y / 2 -
            avatarP2.getGlobalBounds().height / 2
        );
    }

    _playedView.init(_font, DESIGN_W, DESIGN_H);
    // =================================================
    // INPUT BOX (ENERGY)
    // =================================================
    _energyUI.init(_font, DESIGN_W, DESIGN_H);
    // =================================================
    // HAND UI
    // =================================================
    _handUI.init(_font, DESIGN_W, DESIGN_H);
    // =================================================
    // DECIDE START PHASE
    // =================================================
    if (s_IsAIMode) {
        _phase = Phase::SelectBot;
    }
    else {
        _player1 = make_unique<Player>();
        _player2 = make_unique<Player>();
        _current = _player1.get();
        _opponent = _player2.get();
        _deck = make_unique<Deck>();
        _phase = Phase::None;
    }

    // ===== UI SOUND =====
    SoundManager::instance().loadSound(
        "click_anywhere",
        "assets/sound/ui/click_1.ogg"
    );

SoundManager::instance().loadSound(
    "card_click_1",
    "assets/sound/ui/card slide_1.wav"
);

SoundManager::instance().loadSound(
    "card_click_2",
    "assets/sound/ui/cardslide_1.wav"
);

// ===== OPENING SOUND =====
SoundManager::instance().playMusic(
    "assets/sound/bgm/soundgame1.ogg",
    true
);

}

// =====================================================
// BOT SELECT
// =====================================================
void StateNewGame::handleBotSelect(Vector2f mouse)
{
    for (int i = 0; i < botButtons.size(); ++i) {
        if (!botButtons[i].getGlobalBounds().contains(mouse))
            continue;

        _player1 = make_unique<Player>();

        switch (i) {
        case 0: _player2 = make_unique<BotHakari>(); break;
        case 1: _player2 = make_unique<CharlesBoss>(); break;
        case 2: _player2 = make_unique<KashimoBoss>(); break;
        case 3: _player2 = make_unique<UraumeBoss>(); break;
        }

        _current = _player1.get();
        _opponent = _player2.get();
        _deck = make_unique<Deck>();

        _turnCount = 1;
        _isGameOver = false;

        _phase = Phase::None;
        return;
    }
}

// =====================================================
// DRAW HAND
// =====================================================
void StateNewGame::drawHand()
{
    _hand.clear();
    _deck->startNewHand();

    while (_hand.size() < Deck::HAND_SIZE) {
        auto c = _deck->drawCard();
        if (!c) continue;
        _hand.push_back(move(c));
    }
    _handUI.setHand(_hand);
    
}

// =====================================================
// HANDLE
// =====================================================
void StateNewGame::Handle(Event event)
{

    if (_phase == Phase::SelectBot) {
        if (event.type == Event::MouseButtonPressed &&
            event.mouseButton.button == Mouse::Left)
        {
            Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
            handleBotSelect(mouse);
        }
        return;
    }

    if (_isGameOver) {
        SoundManager::instance().stopMusic();
        SoundSource::Status checkMusic;
        if(_isWinGame){
            checkMusic = RM_GI->getWinMusic()->getStatus();
        }
        else{
            checkMusic = RM_GI->getLoseMusic()->getStatus();
        }
        
        if (checkMusic != sf::Music::Playing) {
            RM_GI->getBackgroundMusic()->play();
        }
  
        if ((event.type == Event::MouseButtonPressed &&
            (event.mouseButton.button == Mouse::Left)) || (event.type == Event::KeyPressed)){
                RM_GI->getWinMusic()->stop();
                RM_GI->getLoseMusic()->stop();
                StateManager::getInstance()->ChangeState(0);
            }
        
        return;
    }

    if (event.type == Event::KeyPressed &&
        event.key.code == Keyboard::Escape)
    {
        SoundManager::instance().stopMusic();

        StateManager::getInstance()->ChangeState(0);
    }

    if (_phase == Phase::None) {
        if (_waitForNextTurn)
        {
            _waitForNextTurn = false;
            return;   
        }
        _current->resetTurnState();

        if (_scheduler.hasEffect(_current, EffectTag::Stun)) {

            _battle->onTurnEnd(*_current);
            processEndOfTurn();
            if (_isGameOver) return;
            endTurn();
            return;
        }

        drawHand();

        // ===== ĐỔI SANG NHẠC COMBAT =====
        if (!_combatMusicStarted) {
            SoundManager::instance().stopMusic();
            SoundManager::instance().playMusic(
                "assets/sound/bgm/soundgame2.OGG",
                true
            );
            _combatMusicStarted = true;
        }

        _battle->onTurnStart(*_current);

        // =======================
        // BOT TURN
        // =======================
        if (_current->isBot()) {
            handleBotTurn();
            return;
        }

        // =======================
        // PLAYER TURN
        // =======================
        if (!_scheduler.hasEffect(_current, EffectTag::Jackpot)) {
            _energyUI.clear();
            _phase = Phase::InputEnergy;
        }
        else {
            _phase = Phase::PickCards;
        }

    }

    if (_phase == Phase::InputEnergy) {

        _energyUI.handleEvent(event);

        if (_phase == Phase::InputEnergy && _energyUI.isConfirmed())
        {
            int atk = _energyUI.getAtk();
            int def = _energyUI.getDef();
            int jp  = _energyUI.getJP();

            if (atk + def + jp != Player::MAX_CURSED_ENERGY)
            {
                pushStatusText("WRONG !!! ENSURE THE TOTAL IS 5");
                pushStatusText("TOTAL NOW IS " + std::to_string(atk+def+jp));
                RM_GI->getSound("wrongbeep_2.ogg")->play();
                _energyUI.resetConfirm();
                return;
            }

            _current->allocateCursedEnergy(atk, def, jp);
            _energyUI.resetConfirm();
            _phase = Phase::PickCards;
        }
        return;
    }

    
    else if (_phase == Phase::PickCards)
    {
        _handUI.handleEvent(event);   

        if (_handUI.isConfirmed())
        {
            auto picked = _handUI.getPicked();   

            recordPlayedCards(_current, picked);
            
            for (int idx : picked)
                _hand[idx]->execute(*_current, *_opponent, *this);

            _handUI.clearPick();

            _battle->onTurnEnd(*_current);
            processEndOfTurn();

            if (!_isGameOver)
                endTurn();
        }
    }

}

// =====================================================
// END TURN
// =====================================================
void StateNewGame::swapTurns() {
    swap(_current, _opponent);
    _turnCount++;
}

void StateNewGame::endTurn() {
    _scheduler.tickPlayer(*_current);
    swapTurns();
    _handUI.clearPick();
    _phase = Phase::None;
    _waitForNextTurn = true;  
}

void StateNewGame::processEndOfTurn() {
    if (_current->getHp() <= 0 || _opponent->getHp() <= 0) {
        if(_current->getHp() <= 0)
        {
            _isWinGame = false;
        }
        else
        {
            _isWinGame = true;
        }
        _isGameOver = true;
        _showGameOver = true;

        SoundManager::instance().stopMusic();
        if (_isWinGame) {
            RM_GI->getWinMusic()->play();
        } else {
            RM_GI->getLoseMusic()->play(); 
        }


        _gameOverClock.restart();
        _gameOverFrame = 0;
    }
}

// =====================================================
// BOT TURN
// =====================================================
void StateNewGame::handleBotTurn()
{
    pushStatusText("AI TURN");

    BotController::runTurn(
        _current,
        _opponent,
        _hand,
        this,
        _battle
    );

    processEndOfTurn();
    if (!_isGameOver)
        endTurn();
}


void StateNewGame::pushStatusText(const std::string& text)
{
    _statusQueue.push_back({ text, STATUS_DURATION });

    _statusClock.restart();      
    _lastStatusTime = 0.f;     

    const size_t MAX_STATUS = 10;
    if (_statusQueue.size() > MAX_STATUS)
        _statusQueue.pop_front();
}

void StateNewGame::recordPlayedCards(Player* owner, std::vector<int>& picked){
    bool isP1 = owner == _player1.get();
    _playedView.setPlayedCards(isP1, owner, picked, _hand);
}
// =====================================================
// RENDER
// =====================================================
void StateNewGame::Render(RenderWindow* window)
{
    // for game over
    if (_showGameOver && _gameOverTexture) {
        if (_gameOverClock.getElapsedTime().asSeconds() >= GAME_OVER_FRAME_TIME) {
            _gameOverFrame++;

            if (_gameOverFrame >= GAME_OVER_FRAME_COUNT)
                _gameOverFrame = GAME_OVER_FRAME_COUNT - 1;

            _gameOverRect.left = _gameOverFrame * 96;
            _gameOverSprite.setTextureRect(_gameOverRect);

            _gameOverClock.restart();
        }
    }

    // for status message
    float now = _statusClock.getElapsedTime().asSeconds();
    float dt = now - _lastStatusTime;
    _lastStatusTime = now;

    for (auto it = _statusQueue.begin(); it != _statusQueue.end(); ) {
        it->lifetime -= dt;
        if (it->lifetime <= 0.f)
            it = _statusQueue.erase(it);
        else
            ++it;
    }

    // =================================================
    // BACKGROUND
    // =================================================
    window->draw(m_Background);

    // =================================================
    // GAME OVER DRAW
    // =================================================
    if (_showGameOver) {
        window->draw(_gameOverSprite);
        return; 
    }
    
    // =================================================
    // STATUS TEXT RENDER
    // =================================================
    float centerX = (DESIGN_W / 2.f) * sx;
    float startY  = (DESIGN_H * 0.16f) * sy;
    float lineGap = 54.f * sy;

    int i = 0;
    for (auto& msg : _statusQueue) {
        Text t;
        t.setFont(*_font);
        t.setCharacterSize(static_cast<unsigned>(18 * sy));
        t.setString(msg.text);

        float alpha = 255.f * (msg.lifetime / STATUS_DURATION);
        t.setOutlineThickness(1.f);
        t.setOutlineColor(Color(0, 0, 0, static_cast<Uint8>(alpha * 0.8f)));

        auto b = t.getLocalBounds();
        t.setOrigin(b.width / 2.f, 0.f);
        t.setPosition(centerX, startY + i * lineGap);

        window->draw(t);
        ++i;
    }

    if (_phase == Phase::SelectBot) {
        window->draw(panelBot);
        for (int i = 0; i < botButtons.size(); ++i) {
            window->draw(botButtons[i]);
            window->draw(botTexts[i]);
        }
        return;
    }
    
    // ===== HUD =====
    txtTurn.setString(
        "TURN " + to_string(_turnCount) +
        (_current == _player1.get() ? " - P1" : " - P2")
    );

    txtP1_HP.setString("HP: " + to_string(_player1->getHp()));
    txtP1_Rage.setString("RAGE: " + to_string(_player1->getRage()));
    txtP1_Shield.setString("SHIELD: " + to_string(_player1->getShield()));

    txtP2_HP.setString("HP: " + to_string(_player2->getHp()));
    txtP2_Rage.setString("RAGE: " + to_string(_player2->getRage()));
    txtP2_Shield.setString("SHIELD: " + to_string(_player2->getShield()));
    
    window->draw(panelP1);
    window->draw(panelP2);
    window->draw(txtTurn);

    window->draw(txtP1_HP);
    window->draw(txtP1_Rage);
    window->draw(txtP1_Shield);
    window->draw(txtP2_HP);
    window->draw(txtP2_Rage);
    window->draw(txtP2_Shield);
    window->draw(avatarP1);
    window->draw(avatarP2);
    
    _playedView.draw(window);



    if (_phase == Phase::InputEnergy) {

        _energyUI.draw(window);
    }


    _handUI.draw(window);

}
