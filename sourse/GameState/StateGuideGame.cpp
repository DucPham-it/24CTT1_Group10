#include "StateGuideGame.h"
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

    // ===== COMMON TEXT STYLE =====

    sf::Color DARK_TEXT(255, 255, 255, 200);
    sf::Color OUTLINE(30, 30, 30, 30);

    // ===== GUIDE COLUMN 1 =====
    m_GuideTextCol1.setFont(*font);
    m_GuideTextCol1.setCharacterSize(36);
    m_GuideTextCol1.setFillColor(DARK_TEXT);
    m_GuideTextCol1.setOutlineColor(OUTLINE);
    m_GuideTextCol1.setOutlineThickness(2.f);
    m_GuideTextCol1.setString(
        "\nCAC CHI SO CO BAN:\n"
        "- MAU\n"
        "- DAME CO BAN\n"
        "- THANH NO\n\n"

        "LUOT CUA NGUOI CHOI GOM 3 PHAN:\n\n"

        "PHAN 1: PHAN BO CHU LUC\n"
        "- MOI LUOT CO 5 DIEM CHU LUC\n"
        "- TAN CONG: +10% DAME MOI DIEM\n"
        "- PHONG THU: -10% DAME NHAN VAO\n"
        "- JACKPOT: CONG DON VAO THANH NO\n"
        "- THANH NO TOI DA 36 DIEM\n"
        "- MOI DIEM NO +2% TI LE TRUNG JACKPOT\n\n"

        "PHAN 2: CHON LA BAI\n"
        "- MOI LUOT RUT NGAU NHIEN 6 LA\n"
        "- CHON 3 LA DE SU DUNG\n\n"
    );

    // ===== GUIDE COLUMN 2 =====
    m_GuideTextCol2.setFont(*font);
    m_GuideTextCol2.setCharacterSize(36);
    m_GuideTextCol2.setFillColor(DARK_TEXT);
    m_GuideTextCol2.setOutlineColor(OUTLINE);
    m_GuideTextCol2.setOutlineThickness(2.f);
    m_GuideTextCol2.setString(
        "HUONG DAN CHOI GAME\n\n"

        "DAY LA GAME DOI KHANG THEO LUOT,\n"
        "NGUOI CHOI DI TRUOC.\n\n"

        "CHI TIET CAC LA BAI:\n\n"

        "NHOM HIEU UNG:\n"
        "- TANG 3 DIEM THANH NO II\n"
        "- QUAY JACKPOT\n"
        "- QUAY JACKPOT 2 LAN\n\n"

        "NHOM PHONG THU:\n"
        "- PHONG THU THUONG (HIEU QUA CAO)\n"
        "- PHONG THU +1 DIEM THANH NO\n"
        "- 60% NE DON\n\n"

        "NHOM GAY SAT THUONG:\n"
        "- TAN CONG THUONG (DAME CAO)\n"
        "- TAN CONG + CHOANG 1 LUOT\n"
        "- TAN CONG PHA GIAP\n"
    );

    // ===== GUIDE COLUMN 3 =====
    m_GuideTextCol3.setFont(*font);
    m_GuideTextCol3.setCharacterSize(36);
    m_GuideTextCol3.setFillColor(DARK_TEXT);
    m_GuideTextCol3.setOutlineColor(OUTLINE);
    m_GuideTextCol3.setOutlineThickness(2.f);
    m_GuideTextCol3.setString(
        "\nQUAY JACKPOT:\n"
        "- NEU TRUNG, 5 LUOT TIEP THEO\n"
        "  HAKARI HOI 100% MAU\n"
        "- BO QUA PHAN PHAN BO CHU LUC\n"
        "- TU DONG DON 5 DIEM TAN CONG\n"
        "- LAN DAU TRUNG JACKPOT,\n"
        "  DOI PHUONG BI CHOANG 1 LUOT\n\n"

        "LUOT CUA BOSS:\n"
        "- BOSS CO PHAN 1 VA 2 TUONG TU\n"
        "- KHONG CO LA NHOM HIEU UNG\n"
        "- THANH NO DUNG DE DUNG CHIEU\n"
        "- MOI LUOT TU DONG +1 DIEM NO\n"
        "- DUNG CHIEU SE RESET VE 0\n\n"

        "DO KHO DE:\n"
        "CHARLES BERNARD\n"
        "- NOI TAI: NE DON MOI 3 LUOT\n"
        "- KHONG CO CHIEU DAC BIET\n\n"

        "DO KHO TRUNG BINH:\n"
        "KASHIMO\n"
        "- NOI TAI: DAME VA THU RAT CAO\n"
        "- CHIEU: SAT THUONG SET MANH\n"
        "- DAY NO SAU MOI 4 LUOT\n\n"

        "DO KHO KHO:\n"
        "URAUME\n"
        "- NOI TAI: BANG NGUNG CHU PHAP\n"
        "- JACKPOT KHONG HOI DAY MAU\n"
        "- TRU 40% PHONG THU CUA HAKARI\n"
        "- CHIEU: TAO COT BANG CHAN TAN CONG\n"
        "- DAY NO SAU MOI 2 LUOT\n\n"
    );

    // ===== FOOTER (NOI BAT) =====
    m_GuideFooter.setFont(*font);
    m_GuideFooter.setCharacterSize(36);
    m_GuideFooter.setFillColor(sf::Color(120, 30, 30));
    m_GuideFooter.setOutlineColor(sf::Color::White);
    m_GuideFooter.setOutlineThickness(2.f);
    m_GuideFooter.setString(
        "CHUC BAN CHOI GAME VUI VE!\n"
        "~AN ESC DE QUAY LAI MENU CHINH!~"
    );

    // ===== POSITION & LAYOUT =====
    m_TextOffsetY = 100.f;

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
