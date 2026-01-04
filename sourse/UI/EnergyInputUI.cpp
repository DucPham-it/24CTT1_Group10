#include "EnergyInputUI.h"

using namespace sf;

void EnergyInputUI::InputBox::handleEvent(Event& e)
{
    if (!active) return;

    if (e.type == Event::TextEntered) {
        if (e.text.unicode >= '0' && e.text.unicode <= '9') {
            value += (char)e.text.unicode;
            text.setString(value);
        }
        if (e.text.unicode == 8 && !value.empty()) {
            value.pop_back();
            text.setString(value);
        }
    }
}

int EnergyInputUI::InputBox::getInt() const {
    return value.empty() ? 0 : std::stoi(value);
}

void EnergyInputUI::InputBox::clear() {
    value.clear();
    text.setString("");
}

void EnergyInputUI::init(Font* font, float W, float H)
{
    sx = WM_GI->getScaleX();
    sy = WM_GI->getScaleY();
    DESIGN_W = W;
    DESIGN_H = H;

    auto setupBox = [&](InputBox& b, float x, float y) {
        b.box.setSize({ 50 * sx, 30 * sy });
        b.box.setPosition(x * sx,y *sy);
        b.box.setFillColor(Color(40,40,40));
        b.text.setFont(*font);
        b.text.setCharacterSize(static_cast<unsigned>(22 * sy));
        b.text.setPosition(
            (x + 8) * sx,
            (y + 4) * sy
        );
    };

    float energyY = DESIGN_H * 0.5f;

    setupBox(atkBox, DESIGN_W / 2 - 130, energyY);
    setupBox(defBox, DESIGN_W / 2 - 45,  energyY);
    setupBox(jpBox,  DESIGN_W / 2 + 40,  energyY);

    auto setupLabel = [&](Text& t, const std::string& s, float x, float y){
        t.setFont(*font);
        t.setCharacterSize(static_cast<unsigned>(20 * sy));
        t.setFillColor(sf::Color::White);
        t.setString(s);
        t.setPosition(x * sx, y * sy);
    };
    setupLabel(
        txtAtk, "ATK",
        (DESIGN_W / 2 - 130) + 10,
        energyY - 28
    );

    setupLabel(
        txtDef, "DEF",
        (DESIGN_W / 2 - 45) + 10,
        energyY - 28
    );

    setupLabel(
        txtJP, "JP",
        (DESIGN_W / 2 + 40) + 15,
        energyY - 28
    );

    txtHint.setFont(*font);
    txtHint.setCharacterSize(static_cast<unsigned>(20 * sy));
    txtHint.setFillColor(Color(220,220,10));
    txtHint.setString("Point allocation, total must be 5");
    txtHint.setPosition(
        (DESIGN_W / 2) * sx - txtHint.getLocalBounds().width / 2,
        (energyY - 50) * sy
    );

    btnConfirm.setSize({ 130 * sx, 30 * sy });
    btnConfirm.setPosition(
        (DESIGN_W / 2.3f) * sx,
        (DESIGN_H * 0.55f) * sy
    );
    btnConfirm.setFillColor(Color(80,80,200));
    txtConfirm.setFont(*font);
    txtConfirm.setCharacterSize(static_cast<unsigned>(22 * sy));
    txtConfirm.setString("CONFIRM");
    txtConfirm.setPosition(
        btnConfirm.getPosition().x + 10 * sx,
        btnConfirm.getPosition().y + 6 * sy
    );

    updateFocus();
}

void EnergyInputUI::updateFocus()
{
    atkBox.active = (_focus == 0);
    defBox.active = (_focus == 1);
    jpBox.active  = (_focus == 2);

    atkBox.box.setOutlineThickness(atkBox.active?3.f:0);
    defBox.box.setOutlineThickness(defBox.active?3.f:0);
    jpBox.box.setOutlineThickness(jpBox.active?3.f:0);

    atkBox.box.setOutlineColor(Color::Cyan);
    defBox.box.setOutlineColor(Color::Cyan);
    jpBox.box.setOutlineColor(Color::Cyan);
}

void EnergyInputUI::handleEvent(Event& e)
{
    // =====================
    // MOUSE SUPPORT (ADD-ON)
    // =====================
    if (e.type == sf::Event::MouseButtonPressed &&
        e.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mouse(e.mouseButton.x, e.mouseButton.y);

        // Click ATK
        if (atkBox.box.getGlobalBounds().contains(mouse))
            _focus = 0;

        // Click DEF
        else if (defBox.box.getGlobalBounds().contains(mouse))
            _focus = 1;

        // Click JP
        else if (jpBox.box.getGlobalBounds().contains(mouse))
            _focus = 2;

        // Click CONFIRM
        else if (btnConfirm.getGlobalBounds().contains(mouse))
            _confirmed = true;

        updateFocus();
        return;
    }

    if (e.type == Event::KeyPressed && e.key.code == Keyboard::Tab) {
        _focus = (_focus + 1) % 3;
        updateFocus();
    }

    atkBox.handleEvent(e);
    defBox.handleEvent(e);
    jpBox.handleEvent(e);

    if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
        _confirmed = true;

    
}

void EnergyInputUI::handleMouse(Vector2f mouse)
{
    if (atkBox.box.getGlobalBounds().contains(mouse)) _focus = 0;
    if (defBox.box.getGlobalBounds().contains(mouse)) _focus = 1;
    if (jpBox.box.getGlobalBounds().contains(mouse))  _focus = 2;
    updateFocus();

    if (btnConfirm.getGlobalBounds().contains(mouse))
        _confirmed = true;
}

void EnergyInputUI::draw(RenderWindow* w)
{
    w->draw(txtHint);
    w->draw(txtAtk); w->draw(txtDef); w->draw(txtJP);

    w->draw(atkBox.box); w->draw(defBox.box); w->draw(jpBox.box);
    w->draw(atkBox.text); w->draw(defBox.text); w->draw(jpBox.text);

    w->draw(btnConfirm);
    w->draw(txtConfirm);
}
void EnergyInputUI::forceConfirm()
{
    _confirmed = true;
}

bool EnergyInputUI::isConfirmed() const { return _confirmed; }
void EnergyInputUI::resetConfirm(){ _confirmed = false; }

int EnergyInputUI::getAtk() const { return atkBox.getInt(); }
int EnergyInputUI::getDef() const { return defBox.getInt(); }
int EnergyInputUI::getJP() const { return jpBox.getInt(); }

void EnergyInputUI::clear()
{
    atkBox.clear();
    defBox.clear();
    jpBox.clear();
    _focus = 0;
    updateFocus();
}
