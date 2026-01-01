#include "StateMenu.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/StateManager.h"

// =======================
// CTOR / DTOR
// =======================
StateMenu::StateMenu()
{
    m_PositionMouseX = m_PositionMouseY = 0;
    m_SpriteList.resize(13);
    m_IsMoveIntoButton = false;
}

StateMenu::~StateMenu() {}

void StateMenu::Exit() {}
void StateMenu::Pause() {}
void StateMenu::Resume() {}

// =======================
// CHECK HOVER
// =======================
bool StateMenu::isMovedIntoButton(unsigned int x, unsigned int y)
{
    for (size_t i = 3; i < 8; i++) { // 4 nút menu
        if (m_SpriteList[i].getGlobalBounds().contains(
            static_cast<float>(x),
            static_cast<float>(y)))
        {
            return true;
        }
    }
    return false;
}

// =======================
// INIT
// =======================
void StateMenu::Init()
{
    Texture* texture;

    auto checkMusic = RM_GI->getBackgroundMusic()->getStatus();
    if (checkMusic != sf::Music::Playing) {
        RM_GI->getBackgroundMusic()->play();
    }

    vector<string> texturePath = {
        "background.png",
        "ui.png",
        "title-menu.png",

        "button-menu-newgame.png",
        "button-menu-guide.png",
        "button-menu-settings.png",
        "button-menu-exit.png",
        "button-menu-member.png",

        "hoveredbutton-menu-newgame.png",
        "hoveredbutton-menu-guide.png",
        "hoveredbutton-menu-settings.png",
        "hoveredbutton-menu-exit.png",
        "hoveredbutton-menu-member.png"
    };

    vector<Vector2f> texturePos = {
        {0.f, 0.f},
        {320.f * WM_GI->getScaleX(), 50.f * WM_GI->getScaleY()},
        {580.f * WM_GI->getScaleX(), 120.f * WM_GI->getScaleY()},

        {470.f * WM_GI->getScaleX(), 240.f * WM_GI->getScaleY()}, // Mode Game
        {470.f * WM_GI->getScaleX(), 360.f * WM_GI->getScaleY()}, // Guide Game
        {470.f * WM_GI->getScaleX(), 480.f * WM_GI->getScaleY()}, // Settings
        {470.f * WM_GI->getScaleX(), 600.f * WM_GI->getScaleY()}, // Exit
        {390.f * WM_GI->getScaleX(), 600.f * WM_GI->getScaleY()}, // Member

        {470.f * WM_GI->getScaleX(), 240.f * WM_GI->getScaleY()},
        {470.f * WM_GI->getScaleX(), 360.f * WM_GI->getScaleY()},
        {470.f * WM_GI->getScaleX(), 480.f * WM_GI->getScaleY()},
        {470.f * WM_GI->getScaleX(), 600.f * WM_GI->getScaleY()},
        {390.f * WM_GI->getScaleX(), 600.f * WM_GI->getScaleY()}
    };

    vector<Vector2f> textureScale = {
        {WM_GI->getWidthScreen() / 1301.f, WM_GI->getHeightScreen() / 989.f},
        {470.f * WM_GI->getScaleX() / 187.f, WM_GI->getHeightScreen() / 490.f},
        {5.f * WM_GI->getScaleX(), 5.f * WM_GI->getScaleY()},

        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {2.0f * WM_GI->getScaleX(), 2.0f * WM_GI->getScaleY()},

        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {4.5f * WM_GI->getScaleX(), 4.5f * WM_GI->getScaleY()},
        {2.0f * WM_GI->getScaleX(), 2.0f * WM_GI->getScaleY()}
    };

    for (size_t i = 0; i < texturePath.size(); i++) {
        texture = RM_GI->getTexture(texturePath[i]);
        m_SpriteList[i].setTexture(*texture);
        m_SpriteList[i].setPosition(texturePos[i]);
        m_SpriteList[i].setScale(textureScale[i]);
    }
}

// =======================
// HANDLE EVENT
// =======================
void StateMenu::Handle(Event event)
{
    if (event.type == Event::KeyPressed &&
        event.key.code == Keyboard::Escape)
    {
        StateManager::getInstance()->Quit();
        return;
    }

    if (event.type == Event::MouseMoved) {
        m_PositionMouseX = event.mouseMove.x;
        m_PositionMouseY = event.mouseMove.y;

        if (!m_IsMoveIntoButton &&
            isMovedIntoButton(m_PositionMouseX, m_PositionMouseY))
        {
            RM_GI->getMovedIntoSpriteSound()->play();
            m_IsMoveIntoButton = true;
        }
        else if (!isMovedIntoButton(m_PositionMouseX, m_PositionMouseY)) {
            m_IsMoveIntoButton = false;
        }
    }

    if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Left)
    {
        float mouseX = static_cast<float>(event.mouseButton.x);
        float mouseY = static_cast<float>(event.mouseButton.y);

        for (size_t i = 3; i < 8; i++) {
            if (m_SpriteList[i].getGlobalBounds().contains(mouseX, mouseY)) {

                RM_GI->getClickSound()->play();

                if (i == 3) {                //Mode game 
                    StateManager::getInstance()->ChangeState(1);
                }
                else if (i == 4) {           //Guide game
                    StateManager::getInstance()->ChangeState(5);
                }
                else if (i == 5) {           // Settings     
                    StateManager::getInstance()->ChangeState(2);
                }
                else if (i == 6) {           // Exit
                    StateManager::getInstance()->Quit();
                }
                else if (i == 7) {            // Member
                    StateManager::getInstance()->ChangeState(3);
                }
                return;
            }
        }
    }
}

// =======================
// RENDER
// =======================
void StateMenu::Render(RenderWindow* window)
{
    for (size_t i = 0; i < 8; i++) {
        window->draw(m_SpriteList[i]);

        if (i >= 3 &&
            m_SpriteList[i].getGlobalBounds().contains(
                static_cast<float>(m_PositionMouseX),
                static_cast<float>(m_PositionMouseY)))
        {
            window->draw(m_SpriteList[i + 5]); // hover sprite
        }
    }
}
