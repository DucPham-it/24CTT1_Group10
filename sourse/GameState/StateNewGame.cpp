#include "StateNewGame.h"

#include "../GameManager/StateManager.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/WindowManager.h"
#include "../GameManager/SoundManager.h"

#include "../GameObject/NewGameConfig/GameConfig.h"
#include "../GameObject/BattleSystem/BattleSystem.h"
#include "../GameObject/Card/Card.h"

// ===== AI =====
#include "../GameObject/AI/BotPlayer.h"
#include "../GameObject/AI/BotHakari.h"
#include "../GameObject/AI/CharlesBoss.h"
#include "../GameObject/AI/KashimoBoss.h"
#include "../GameObject/AI/UraumeBoss.h"

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
    _turnCount(1),
    _phase(Phase::None),
    _font(nullptr)
{
    _battle = new BattleSystem(_scheduler);
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
// INPUT BOX
// =====================================================
void StateNewGame::InputBox::handleEvent(Event& e) {
    if (!active) return;

    if (e.type == Event::TextEntered) {
        if (e.text.unicode >= '0' && e.text.unicode <= '9') {
            value += static_cast<char>(e.text.unicode);
            text.setString(value);
        }
        if (e.text.unicode == 8 && !value.empty()) {
            value.pop_back();
            text.setString(value);
        }
    }
}

int StateNewGame::InputBox::getInt() const {
    return value.empty() ? 0 : stoi(value);
}

void StateNewGame::InputBox::clear() {
    value.clear();
    text.setString("");
}

// =====================================================
// INIT
// =====================================================
void StateNewGame::Init()
{
    RM_GI->getBackgroundMusic()->stop();
    SoundManager::instance().stopMusic();

    GameConfig::instance().loadFromFile(
        "GameConfig/game_config.txt"
    );
    Player::loadConfig();

    _font = RM_GI->getFont("Minecraft.ttf");

    float W = WM_GI->getWidthScreen();
    float H = WM_GI->getHeightScreen();

    // ===== BACKGROUND =====
    if (auto bg = RM_GI->getTexture("battle_bg.png")) {
        m_Background.setTexture(*bg);
        m_Background.setScale(
            W / bg->getSize().x,
            H / bg->getSize().y
        );
    }

    // ===== GAME OVER =====
    _gameOverTexture = RM_GI->getTexture("gameOver-animation.png");

    if (_gameOverTexture) {
        _gameOverRect = sf::IntRect(0, 0, 94, 13);
        _gameOverSprite.setTexture(*_gameOverTexture);
        _gameOverSprite.setTextureRect(_gameOverRect);



        _gameOverSprite.setScale(Vector2f(10.f * WM_GI->getScaleX(), 10.f * WM_GI->getScaleY()));

        _gameOverSprite.setOrigin(40.f, 8.f); 
        _gameOverSprite.setPosition(
            WM_GI->getWidthScreen() / 2.f,
            WM_GI->getHeightScreen() / 2.f
        );
    }

    // =================================================
    // BOT SELECT UI (4 BOSSES)
    // =================================================
    panelBot.setSize({ 500, 300 });
    panelBot.setPosition({ W / 2 - 230, H / 2 - 140 });
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
        btn.setSize({ 320, 42 });
        btn.setPosition(W / 2 - 160, H / 2 - 80 + i * 48);
        btn.setFillColor(Color(120, 120, 180));
        botButtons.push_back(btn);

        Text t;
        t.setFont(*_font);
        t.setCharacterSize(19);
        t.setString(botNames[i]);
        t.setPosition(btn.getPosition() + Vector2f(16, 8));
        botTexts.push_back(t);
    }

    // =================================================
    // HUD PANELS
    // =================================================
    panelP1.setSize({ 300,150});
    panelP1.setPosition({ 20, H - 220 });
    panelP1.setFillColor(Color(0, 0, 0, 150));

    panelP2.setSize({ 300,150 });
    panelP2.setPosition({ W - 320, 20 });
    panelP2.setFillColor(Color(0, 0, 0, 150));

    auto setupText = [&](Text& t, float x, float y, Color c) {
        t.setFont(*_font);
        t.setCharacterSize(30);
        t.setFillColor(c);
        t.setPosition(x, y);
        };

    setupText(txtP1_HP, 40, H - 200, Color::Red);
    setupText(txtP1_Rage, 40, H - 170, Color::Yellow);
    setupText(txtP1_Shield, 40, H - 140, Color::Cyan);

    setupText(txtP2_HP, W - 300, 40, Color::Red);
    setupText(txtP2_Rage, W - 300, 70, Color::Yellow);
    setupText(txtP2_Shield, W - 300, 100, Color::Cyan);

    txtTurn.setFont(*_font);
    txtTurn.setCharacterSize(32);
    txtTurn.setPosition(W / 2 - 80, 10);

    // ===== AVATAR P1 =====
    if (auto tex = RM_GI->getTexture("p1.png")) {
        avatarP1.setTexture(*tex);

        float scale = (panelP1.getSize().y * 0.5f) / tex->getSize().y;
        avatarP1.setScale(scale, scale);

        avatarP1.setPosition(
            panelP1.getPosition().x + avatarP1.getGlobalBounds().width + 250.f,
            panelP1.getPosition().y + panelP1.getSize().y / 2.f
            - avatarP1.getGlobalBounds().height / 2.f
        );
    }

    // ===== AVATAR P2 =====
    if (auto tex = RM_GI->getTexture("p2.png")) {
        avatarP2.setTexture(*tex);

        float scale = (panelP2.getSize().y * 0.5f) / tex->getSize().y;
        avatarP2.setScale(scale, scale);

        avatarP2.setPosition(
            panelP2.getPosition().x - avatarP2.getGlobalBounds().width - 65.f,
            panelP2.getPosition().y + panelP2.getSize().y / 2.f
            - avatarP2.getGlobalBounds().height / 2.f
        );
    }

    // =================================================
    // INPUT BOX (ENERGY)
    // =================================================
    auto setupBox = [&](InputBox& b, float x, float y) {
        b.box.setSize({ 70, 50 });
        b.box.setPosition(x, y);
        b.box.setFillColor(Color(40, 40, 40));
        b.text.setFont(*_font);
        b.text.setCharacterSize(28);
        b.text.setPosition(x + 10, y + 6);
        b.active = false;
        };

    setupBox(atkBox, W / 2 - 130, H * 0.54f);
    setupBox(defBox, W / 2 - 45, H * 0.54f);
    setupBox(jpBox, W / 2 + 40, H * 0.54f);

    btnConfirmEnergy.setSize({ 180,36 });
    btnConfirmEnergy.setPosition(W / 2.2f, H * 0.58f);
    btnConfirmEnergy.setFillColor(Color(80, 80, 200));

    txtConfirmEnergy.setFont(*_font);
    txtConfirmEnergy.setString("CONFIRM");
    txtConfirmEnergy.setPosition(
        btnConfirmEnergy.getPosition() + Vector2f(10, 6)
    );

    // =================================================
    // HAND
    // =================================================
    handOrigin = { W * 0.18f, H * 0.7f };
    handSpacing = (W * 0.7f) / 6.f;

    btnConfirmCards.setSize({ 250,40 });    
    btnConfirmCards.setPosition(W / 2.2f, H * 0.9f);
    btnConfirmCards.setFillColor(Color(80, 160, 80));

    txtConfirmCards.setFont(*_font);
    txtConfirmCards.setString("PLAY CARDS");
    txtConfirmCards.setPosition(
        btnConfirmCards.getPosition() + Vector2f(10, 6)
    );

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

    m_HandUI.clear();
    for (int i = 0; i < _hand.size(); ++i) {
        CardUI ui;
        ui.index = i;
        ui.selected = false;

        if (auto tex = RM_GI->getTexture(_hand[i]->getIconPath())) {
            ui.sprite.setTexture(*tex);
            ui.sprite.setScale(0.55f, 0.55f);
            ui.sprite.setPosition(
                handOrigin.x + i * handSpacing,
                handOrigin.y
            );
            ui.basePos = ui.sprite.getPosition(); 
            m_HandUI.push_back(ui);
        }
    }
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
        auto checkMusic = RM_GI->getWinMusic()->getStatus();

        if (checkMusic != sf::Music::Playing) {
            RM_GI->getBackgroundMusic()->play();
        }
  
        if ((event.type == Event::MouseButtonPressed &&
            (event.mouseButton.button == Mouse::Left)) || (event.type == Event::KeyPressed)){
                RM_GI->getWinMusic()->stop();
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
            return;   // chờ 1 frame trước khi bot đi
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
            atkBox.clear(); defBox.clear(); jpBox.clear();
            atkBox.active = true;
            _phase = Phase::InputEnergy;
        }
        else {
            _phase = Phase::PickCards;
        }

    }

    atkBox.handleEvent(event);
    defBox.handleEvent(event);
    jpBox.handleEvent(event);

    if (event.type == Event::KeyPressed &&
        event.key.code == Keyboard::Enter)
    {
        if (_phase == Phase::InputEnergy)
            handleEnergyConfirm();
        else if (_phase == Phase::PickCards){
            handleCardConfirm();
        }
            
    }

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

        atkBox.active = atkBox.box.getGlobalBounds().contains(mouse);
        defBox.active = defBox.box.getGlobalBounds().contains(mouse);
        jpBox.active = jpBox.box.getGlobalBounds().contains(mouse);

        if (_phase == Phase::InputEnergy &&
            btnConfirmEnergy.getGlobalBounds().contains(mouse))
            handleEnergyConfirm();

        if (_phase == Phase::PickCards) {
            handleCardClick(mouse);
            if (btnConfirmCards.getGlobalBounds().contains(mouse))
                handleCardConfirm();
        }
    }
}

// =====================================================
// ENERGY CONFIRM
// =====================================================
void StateNewGame::handleEnergyConfirm()
{
    int atk = atkBox.getInt();
    int def = defBox.getInt();
    int jp = jpBox.getInt();

    if (atk + def + jp != Player::MAX_CURSED_ENERGY){
        StateNewGame::pushStatusText(format("WRONG !!! ENSURE THE TOTAL IS 5"));
        StateNewGame::pushStatusText(format("TOTAL KNOW IS {}", atk+def+jp));
        return;
    }
    _current->allocateCursedEnergy(atk, def, jp);
    _phase = Phase::PickCards;
}

// =====================================================
// CARD PICK
// =====================================================
void StateNewGame::handleCardClick(sf::Vector2f mouse)
{
    for (auto& ui : m_HandUI) {
        if (!ui.sprite.getGlobalBounds().contains(mouse))
            continue;

        SoundManager::instance().playSound("card_click_1");

        if (ui.selected) {
            ui.selected = false;
            ui.sprite.setColor(sf::Color::White);
            ui.sprite.setPosition(ui.basePos);

            auto it = std::find(_picked.begin(), _picked.end(), ui.index);
            if (it != _picked.end())
                _picked.erase(it);

            return;
        }

        if (_picked.size() < 3) {
            ui.selected = true;
            ui.sprite.setColor(sf::Color(200, 200, 255));
            ui.sprite.setPosition(
                ui.basePos.x,
                ui.basePos.y - 20.f 
            );
            _picked.push_back(ui.index);
        }

        return;
    }
}

void StateNewGame::handleCardConfirm()
{
    if (_picked.size() != 3){
        return;
    }


    for (int idx : _picked)
        _hand[idx]->execute(*_current, *_opponent, *this);

    _battle->onTurnEnd(*_current);
    processEndOfTurn();

    if (!_isGameOver)
        endTurn();
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
    _picked.clear();
    _phase = Phase::None;
    _waitForNextTurn = true;   // ⭐ thêm biến này
}

void StateNewGame::processEndOfTurn() {
    if (_current->getHp() <= 0 || _opponent->getHp() <= 0) {
        _isGameOver = true;
        _showGameOver = true;

        SoundManager::instance().stopMusic();
        RM_GI->getWinMusic()->play();

        _gameOverClock.restart();
        _gameOverFrame = 0;
    }
}

// =====================================================
// BOT TURN
// =====================================================
void StateNewGame::handleBotTurn()
{
    // BOT 
    _current->allocateCursedEnergy();

    // BOT 
    this->pushStatusText(format("AI TURN"));

    auto cards = _current->pickCards(_hand);

    for (auto c : cards)
        c->execute(*_current, *_opponent, *this);

    _battle->onTurnEnd(*_current);
    processEndOfTurn();

    if (!_isGameOver)
        endTurn();
}

void StateNewGame::pushStatusText(const std::string& text)
{
    _statusQueue.push_back({ text, STATUS_DURATION });

    _statusClock.restart();      // ⭐ reset thời gian
    _lastStatusTime = 0.f;       // ⭐ reset delta

    // giới hạn số dòng 
    const size_t MAX_STATUS = 10;
    if (_statusQueue.size() > MAX_STATUS)
        _statusQueue.pop_front();
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



    window->draw(m_Background);

    if (_showGameOver) {
        window->draw(_gameOverSprite);
        return; 
    }
    float centerX = WM_GI->getWidthScreen() / 2.f;
    float startY = WM_GI->getHeightScreen() * 0.2f;
    float lineGap = 54.f;

    int i = 0;
    for (auto& msg : _statusQueue) {
        Text t;
        t.setFont(*_font);
        t.setCharacterSize(24);
        t.setString(msg.text);

        float alpha = 255.f * (msg.lifetime / STATUS_DURATION);
        t.setOutlineThickness(1.f);
        t.setOutlineColor(Color(0, 0, 0, (Uint8)(alpha * 0.8f)));


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

    for (auto& c : m_HandUI)
        window->draw(c.sprite);

    if (_phase == Phase::InputEnergy) {
        window->draw(atkBox.box);
        window->draw(defBox.box);
        window->draw(jpBox.box);
        window->draw(atkBox.text);
        window->draw(defBox.text);
        window->draw(jpBox.text);
        window->draw(btnConfirmEnergy);
        window->draw(txtConfirmEnergy);
    }

    if (_phase == Phase::PickCards) {
        window->draw(btnConfirmCards);
        window->draw(txtConfirmCards);
    }
}
