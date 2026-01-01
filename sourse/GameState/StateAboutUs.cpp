#include "StateAboutUs.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/StateManager.h"

// ==================================================
// CTOR / DTOR
// ==================================================
StateAboutUs::StateAboutUs()
{
    // UI sprite: background, border, right, left, member-image
    m_ListSprite.resize(5);

    m_MemberInfor.resize(6);
    for (size_t i = 0; i < 6; i++)
        m_MemberInfor[i].resize(6);

    // Member textures
    m_MemberTexture.resize(6);

    m_CurrentMember = 0;
}

StateAboutUs::~StateAboutUs()
{
    m_MemberTexture.clear();
}

void StateAboutUs::Exit() {}
void StateAboutUs::Pause() {}
void StateAboutUs::Resume() {}

// ==================================================
// INIT
// ==================================================
void StateAboutUs::Init()
{
    Font* font = RM_GI->getFont("Minecraft.ttf");
    Texture* texture;

    // =========================
    // PATH TEXTURE
    // =========================
    vector<string> pathTexture = {
        "menu-background.png",  
        "member-border.png",    
        "right-arrow.png",      
        "left-arrow.png",       
        "member1.png",          
        "member2.png",
        "member3.png",
        "member4.png",
        "member5.png",
        "member6.png"
    };

    // =========================
    // LOAD MEMBER TEXTURE
    // =========================
    for (size_t i = 0; i < 6; i++) {
        m_MemberTexture[i] = RM_GI->getTexture(pathTexture[i + 4]);
    }

    // =========================
    // SCALE SPRITE UI
    // =========================
    vector<Vector2f> scaleSprite = {
        {1.75f * WM_GI->getScaleX(), 1.5f * WM_GI->getScaleY()},          // background
        {WM_GI->getScaleX() * 5.f, WM_GI->getScaleY() * 5.f},            // border
        {0.4f * WM_GI->getScaleX(), 0.4f * WM_GI->getScaleY()},           // right
        {0.4f * WM_GI->getScaleX(), 0.4f * WM_GI->getScaleY()},           // left
        {0.238f * WM_GI->getScaleX(), 0.243f * WM_GI->getScaleY()}        // member image
    };

    // =========================
    // POSITION SPRITE UI
    // =========================
    vector<Vector2f> positionSprite = {
        {0.f, 0.f},                                                       // background
        {280.f * WM_GI->getScaleX(), 220.f * WM_GI->getScaleY()},         // border
        {1220.f * WM_GI->getScaleX(), 350.f * WM_GI->getScaleY()},        // right
        {30.f * WM_GI->getScaleX(), 350.f * WM_GI->getScaleY()},          // left
        {316.f * WM_GI->getScaleX(), 255.f * WM_GI->getScaleY()}          // member image
    };

    // =========================
    // LOAD UI SPRITES
    // =========================
    for (size_t i = 0; i < m_ListSprite.size(); i++) {
        texture = RM_GI->getTexture(pathTexture[i]);
        m_ListSprite[i].setTexture(*texture);
        m_ListSprite[i].setScale(scaleSprite[i]);
        m_ListSprite[i].setPosition(positionSprite[i]);
    }

    // =========================
    // MEMBER INFORMATION
    // =========================
    vector<vector<string>> memberInfor = {
        {"Huynh Van Duong", "Dao Thanh Phong", "Pham Vo Duc", "Phan The Minh Tri", "Huynh Ba Thi", "Che Nguyen Thuy Trang"},
        {"04/05/2006", "10/09/2006", "19/05/2006", "30/09/2006", "06/08/2006", "30/08/2006"},
        {"Que quan: My", "Que quan: Dong Nai", "Que quan: Da Nang", "Que quan: Viet Nam", "Que quan: Viet Nam", "Que quan: Viet Nam"},
        {"MSSV: 24120176", "MSSV: 24120006", "MSSV: 24120041", "MSSV: 24120506", "MSSV: 24120251", "MSSV: 24120469"},
        {"So thich: An khong ngoi roi", "So thich: Lam wibu", "So thich: Chup anh", "So thich: Ram ai tinh", "So thich: Vibe Coding", "So thich: Xinh la duoc"},
        {"Nhiem vu: Design Template", "Nhiem vu: Design UI, Sound", "Nhiem vu: Design UI, Logic FrontEnd ", "Nhiem vu: Design AI Logic", "Nhiem vu: Design Logic Backend Game", "Nhiem vu: Tester, Make Data"}
    };

    vector<Vector2f> positionText = {
        {620.f * WM_GI->getScaleX(), 220.f * WM_GI->getScaleY()},
        {670.f * WM_GI->getScaleX(), 300.f * WM_GI->getScaleY()},
        {670.f * WM_GI->getScaleX(), 350.f * WM_GI->getScaleY()},
        {670.f * WM_GI->getScaleX(), 400.f * WM_GI->getScaleY()},
        {670.f * WM_GI->getScaleX(), 450.f * WM_GI->getScaleY()},
        {670.f * WM_GI->getScaleX(), 500.f * WM_GI->getScaleY()}
    };

    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 6; j++) {
            m_MemberInfor[i][j].setFont(*font);

            if (i == 0)
                m_MemberInfor[i][j].setCharacterSize(static_cast<unsigned int>(40 * WM_GI->getScaleX()));
            else
                m_MemberInfor[i][j].setCharacterSize(static_cast<unsigned int>(20 * WM_GI->getScaleX()));

            m_MemberInfor[i][j].setFillColor(Color::Black);
            m_MemberInfor[i][j].setString(memberInfor[i][j]);
            m_MemberInfor[i][j].setPosition(positionText[i]);
        }
    }
}

// ==================================================
// HANDLE EVENT
// ==================================================
void StateAboutUs::Handle(Event event)
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

        // Right arrow
        if (m_ListSprite[2].getGlobalBounds().contains(mouse)) {
            m_CurrentMember = (m_CurrentMember + 1) % 6;
            m_ListSprite[4].setTexture(*m_MemberTexture[m_CurrentMember]);
            RM_GI->getClickSound()->play();
        }
        // Left arrow
        else if (m_ListSprite[3].getGlobalBounds().contains(mouse)) {
            m_CurrentMember = (m_CurrentMember == 0) ? 5 : m_CurrentMember - 1;
            m_ListSprite[4].setTexture(*m_MemberTexture[m_CurrentMember]);
            RM_GI->getClickSound()->play();
        }
    }
}

// ==================================================
// RENDER
// ==================================================
void StateAboutUs::Render(RenderWindow* window)
{
    // UI sprites
    for (size_t i = 0; i < m_ListSprite.size(); i++) {
        window->draw(m_ListSprite[i]);
    }

    // Member text
    for (size_t i = 0; i < 6; i++) {
        window->draw(m_MemberInfor[i][m_CurrentMember]);
    }
}
