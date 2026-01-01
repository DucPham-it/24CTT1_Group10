#include "StateModeGame.h"
#include "../GameManager/StateManager.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/WindowManager.h"

// =======================
// CTOR / DTOR
// =======================
StateModeGame::StateModeGame()
    : m_MovedIntoButton(0)
{
    m_ListSprite.resize(5);
}

StateModeGame::~StateModeGame() {}

void StateModeGame::Exit() {}
void StateModeGame::Pause() {}
void StateModeGame::Resume() {}

// =======================
// INIT
// =======================
void StateModeGame::Init()
{
    vector<string> textures = {
        "background.png",        
        "title-choosemode.png",  
        "button-wHuman.png",     
        "button-wAI.png",       
        "ui.png"                
    };

    vector<Vector2f> pos = {
        {0, 0},
        {420.f * WM_GI->getScaleX(), 120.f * WM_GI->getScaleY()},
        {380.f * WM_GI->getScaleX(), 280.f * WM_GI->getScaleY()},
        {700.f * WM_GI->getScaleX(), 280.f * WM_GI->getScaleY()},
        {320.f * WM_GI->getScaleX(), 50.f * WM_GI->getScaleY()}
    };

    vector<Vector2f> scale = {
        {WM_GI->getWidthScreen() / 1301.f, WM_GI->getHeightScreen() / 989.f},
        {5.f * WM_GI->getScaleX(), 5.f * WM_GI->getScaleY()},
        {3.5f * WM_GI->getScaleX(), 3.5f * WM_GI->getScaleY()},
        {3.5f * WM_GI->getScaleX(), 3.5f * WM_GI->getScaleY()},
        {470.f * WM_GI->getScaleX() / 187.f,
         WM_GI->getHeightScreen() / 490.f}
    };

    for (size_t i = 0; i < m_ListSprite.size(); ++i) {
        auto tex = RM_GI->getTexture(textures[i]);
        m_ListSprite[i].setTexture(*tex);
        m_ListSprite[i].setPosition(pos[i]);
        m_ListSprite[i].setScale(scale[i]);
    }
}

// =======================
// HANDLE EVENT
// =======================
void StateModeGame::Handle(Event event)
{
    if (event.type == Event::KeyPressed &&
        event.key.code == Keyboard::Escape)
    {
        StateManager::getInstance()->ChangeState(0);
        return;
    }

    if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Left)
    {
        Vector2f mouse(
            static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y)
        );

        // Player vs Player
        if (m_ListSprite[2].getGlobalBounds().contains(mouse)) {
            StateNewGame::setAIMode(false);
            StateManager::getInstance()->ChangeState(4);
        }
        // Player vs AI
        else if (m_ListSprite[3].getGlobalBounds().contains(mouse)) {
            StateNewGame::setAIMode(true);
            StateManager::getInstance()->ChangeState(4);
        }
    }
}

// =======================
// RENDER 
// =======================
void StateModeGame::Render(RenderWindow* window)
{
    // 1. Background
    window->draw(m_ListSprite[0]);

    // 2. UI
    window->draw(m_ListSprite[4]);

    // 3. Title
    window->draw(m_ListSprite[1]);

    // 4. Buttons
    window->draw(m_ListSprite[2]);
    window->draw(m_ListSprite[3]);
}
