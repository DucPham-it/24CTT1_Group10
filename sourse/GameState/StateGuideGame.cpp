#include "StateGuideGame.h"
#include <sstream>
#include "../GameManager/StateManager.h"
#include "../GameManager/ResourceManager.h"

StateGuideGame::StateGuideGame()
    : m_Font(nullptr),
    m_TextOffsetY(0.f),
    m_ScrollSpeed(30.f),
    m_MinOffsetY(0.f),
    m_MaxOffsetY(0.f)
{
}


std::string StateGuideGame::WrapText(sf::Font& font, const std::string& str, unsigned size, float maxWidth)
{
    std::string result;
    std::string line;
    std::string word;

    for (size_t i = 0; i < str.size(); ++i)
    {
        char c = str[i];

        // Giữ newline gốc
        if (c == '\n')
        {
            result += line + "\n";
            line.clear();
            continue;
        }

        // Tách từ theo space
        if (c == ' ')
        {
            sf::Text test(line + word, font, size);
            if (test.getLocalBounds().width > maxWidth)
            {
                result += line + "\n";
                line = word + " ";
            }
            else
            {
                line += word + " ";
            }
            word.clear();
        }
        else
        {
            word += c;
        }
    }

    // word cuối
    sf::Text test(line + word, font, size);
    if (test.getLocalBounds().width > maxWidth)
        result += line + "\n" + word;
    else
        result += line + word;

    return result;
}


void StateGuideGame::Init() {
    std::cout << ">>> GUIDE STATE INIT <<<\n";

    float W = WM_GI->getWidthScreen();
    float H = WM_GI->getHeightScreen();

    // ===== BACKGROUND =====
    auto bgTex = RM_GI->getTexture("Guide_Background.png");
    m_Background.setTexture(*bgTex);
    m_Background.setScale(
        W / bgTex->getSize().x,
        H / bgTex->getSize().y
    );

    // ===== FONT =====
    auto font = RM_GI->getFont("Minecraft.ttf");
    marginX = 80.f;
    usableWidth = W - marginX * 2.f;
    columnWidth = usableWidth / 3.f;
    // ===== COMMON TEXT STYLE =====

    sf::Color DARK_TEXT(255, 255, 255, 255);
    sf::Color OUTLINE(0, 0, 0, 255);


    auto SetupText = [&](sf::Text& t)
    {
        t.setFont(*font);
        t.setCharacterSize(36);
        t.setFillColor(sf::Color(245,245,245));
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(3.f);
    };
    SetupText(m_GuideTextCol1);
    SetupText(m_GuideTextCol2);
    SetupText(m_GuideTextCol3);

    std::string col1 = 
"CAC CHI SO CO BAN: \n"
"- MAU \n"
"- DAME CO BAN \n"
"- THANH NO \n\n"
"LUOT NGUOI CHOI GOM 3 PHAN: \n\n"
"PHAN 1: PHAN BO CHU LUC \n"
"- MOI LUOT CO 5 DIEM CHU LUC \n"
"- TAN CONG: +10% DAME MOI DIEM \n"
"- PHONG THU: -10% DAME NHAN VAO \n"
"- JACKPOT: CONG DON VAO THANH NO \n"
"- THANH NO TOI DA 36 DIEM \n"
"- MOI DIEM NO +2% TI LE TRUNG JACKPOT \n\n"
"PHAN 2: CHON LA BAI \n"
"- MOI LUOT RUT NGAU NHIEN 6 LA \n"
"- CHON 3 LA DE SU DUNG";

m_GuideTextCol1.setString(WrapText(*font, col1, 36, columnWidth - 20));

    std::string col2 =
"HUONG DAN CHOI GAME \n\n"
"DAY LA GAME DOI KHANG THEO LUOT, NGUOI CHOI DI TRUOC. \n\n"
"CHI TIET CAC LA BAI: \n\n"
"NHOM HIEU UNG: \n"
"- TANG 3 DIEM THANH NO \n"
"- QUAY JACKPOT \n"
"- QUAY JACKPOT 2 LAN \n\n"
"NHOM PHONG THU: \n"
"- PHONG THU THUONG \n"
"- PHONG THU +1 DIEM THANH NO \n"
"- 60% NE DON \n\n"
"NHOM GAY SAT THUONG: \n"
"- TAN CONG THUONG \n"
"- TAN CONG + CHOANG \n"
"- TAN CONG PHA GIAP";

m_GuideTextCol2.setString(WrapText(*font, col2, 36, columnWidth - 20));

    std::string col3 =
"QUAY JACKPOT:\n"
"- NEU TRUNG, 5 LUOT TIEP THEO HOI DAY MAU \n"
"- BO QUA PHAN PHAN BO CHU LUC \n"
"- TU DONG DON 5 DIEM TAN CONG \n"
"- LAN DAU TRUNG, DOI PHUONG BI CHOANG \n\n"
"LUOT CUA BOSS: \n"
"- BOSS KHONG CO LA HIEU UNG \n"
"- THANH NO DUNG DE DUNG CHIEU \n"
"- MOI LUOT +1 DIEM NO \n\n"
"DO KHO: \n"
"CHARLES: NE DON MOI 3 LUOT \n"
"KASHIMO: DAME RAT CAO \n"
"URAUME: BANG HOA & PHA GIAP";

m_GuideTextCol3.setString(WrapText(*font, col3, 36, columnWidth - 20));


    // ===== FOOTER (NOI BAT) =====
    m_GuideFooter.setFont(*font);
    m_GuideFooter.setCharacterSize(32);
    m_GuideFooter.setFillColor(sf::Color(120, 30, 30));
    m_GuideFooter.setOutlineColor(sf::Color::White);
    m_GuideFooter.setOutlineThickness(3.f);
    m_GuideFooter.setString(
        "CHUC BAN CHOI GAME VUI VE!\n"
        "~AN ESC DE QUAY LAI MENU CHINH!~"
    );

    // ===== POSITION & LAYOUT =====
    m_TextOffsetY = 120.f;

    float marginX = 80.f;
    float usableWidth = W - marginX * 2;
    float columnWidth = usableWidth / 3.f;

    m_GuideTextCol1.setPosition(marginX, m_TextOffsetY);
    m_GuideTextCol2.setPosition(marginX + columnWidth, m_TextOffsetY);
    m_GuideTextCol3.setPosition(marginX + columnWidth * 2, m_TextOffsetY);

    m_GuideFooter.setPosition(
        W / 2.f - m_GuideFooter.getLocalBounds().width / 2.f,
        m_TextOffsetY + 900.f
    );

    // ===== SCROLL CONFIG =====
    m_ScrollSpeed = 30.f;
    m_MinOffsetY = 80.f;

    float textHeight = m_GuideTextCol3.getLocalBounds().height + 900.f;
    float viewHeight = H - 120.f;

    if (textHeight > viewHeight)
        m_MaxOffsetY = viewHeight - textHeight;
    else
        m_MaxOffsetY = m_MinOffsetY;
}

void StateGuideGame::Handle(Event event) {
    if (event.type == Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            m_TextOffsetY += m_ScrollSpeed;
        else
            m_TextOffsetY -= m_ScrollSpeed;
    }

    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Up)
            m_TextOffsetY += m_ScrollSpeed;
        if (event.key.code == Keyboard::Down)
            m_TextOffsetY -= m_ScrollSpeed;

        if (event.key.code == Keyboard::Escape)
            StateManager::getInstance()->ChangeState(0);
    }

    if (m_TextOffsetY > m_MinOffsetY)
        m_TextOffsetY = m_MinOffsetY;
    if (m_TextOffsetY < m_MaxOffsetY)
        m_TextOffsetY = m_MaxOffsetY;

    float marginX = 80.f;
    float usableWidth = WM_GI->getWidthScreen() - marginX * 2;
    float columnWidth = usableWidth / 3.f;

    m_GuideTextCol1.setPosition(marginX, m_TextOffsetY);
    m_GuideTextCol2.setPosition(marginX + columnWidth, m_TextOffsetY);
    m_GuideTextCol3.setPosition(marginX + columnWidth * 2, m_TextOffsetY);

    m_GuideFooter.setPosition(
        WM_GI->getWidthScreen() / 2.f - m_GuideFooter.getLocalBounds().width / 2.f,
        m_TextOffsetY + 900.f
    );
}

void StateGuideGame::Render(RenderWindow* window) {
    window->draw(m_Background);
    window->draw(m_GuideTextCol1);
    window->draw(m_GuideTextCol2);
    window->draw(m_GuideTextCol3);
    window->draw(m_GuideFooter);
}

void StateGuideGame::Pause() {}
void StateGuideGame::Resume() {}
void StateGuideGame::Exit() {}
