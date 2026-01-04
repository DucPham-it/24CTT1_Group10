#include "HandUI.h"

using namespace sf;

void HandUI::init(Font* font, float W, float H)
{
    sx = WM_GI->getScaleX();
    sy = WM_GI->getScaleY();

    DESIGN_W = W;
    DESIGN_H = H;

    _origin = {
        DESIGN_W * 0.16f * sx,
        DESIGN_H * 0.64f * sy
    };
    _spacing = (DESIGN_W * 0.7f / 6.f) * sx;

    _btnConfirm.setSize({ 170 * sx,30 * sy });
    _btnConfirm.setPosition(
        (DESIGN_W / 2.23f) * sx,
        (DESIGN_H * 0.9f) * sy
    );
    _btnConfirm.setFillColor(Color(80,160,80));

    _txtConfirm.setFont(*font);
    _txtConfirm.setCharacterSize(static_cast<unsigned>(22 * sy));
    _txtConfirm.setString("PLAY CARDS");
    _txtConfirm.setPosition(
        _btnConfirm.getPosition().x + 8 * sx,
        _btnConfirm.getPosition().y + 4 * sy
    );
}

void HandUI::setHand(std::vector<std::unique_ptr<Card>>& cards)
{
    _slots.clear();
    _picked.clear();
    _confirmed = false;

    for (int i = 0; i < cards.size(); ++i)
    {
        CardSlot s;
        s.index = i;

        if (auto tex = RM_GI->getTexture(cards[i]->getIconPath()))
        {
            s.sprite.setTexture(*tex);
            s.sprite.setScale(0.3f * sx, 0.3f * sy);;
            s.sprite.setPosition(_origin.x + i * _spacing, _origin.y);
            s.basePos = s.sprite.getPosition();
        }

        _slots.push_back(s);
    }
    
}

void HandUI::handleEvent(Event& e)
{
    // ENTER confirm
    if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
    {
        if (_picked.size() == 3)
            _confirmed = true;
        return;
    }

    if (e.type != Event::MouseButtonPressed ||
        e.mouseButton.button != Mouse::Left)
        return;

    Vector2f mouse(
        (float)e.mouseButton.x,
        (float)e.mouseButton.y
    );
    
    if(_txtConfirm.getGlobalBounds().contains(mouse))
    {
        if (_picked.size() == 3)
            _confirmed = true;
        return;
    }
    for (auto& c : _slots)
    {
        if (!c.sprite.getGlobalBounds().contains(mouse))
            continue;

        

        if (c.selected)
        {
            SoundManager::instance().playSound("card_click_1");
            c.selected = false;
            c.sprite.setColor(Color::White);
            c.sprite.setPosition(c.basePos);

            auto it = std::find(_picked.begin(), _picked.end(), c.index);
            if (it != _picked.end()) _picked.erase(it);
        }
        else if (_picked.size() < 3)
        {
            SoundManager::instance().playSound("card_click_1");
            c.selected = true;
            c.sprite.setColor(Color(200,200,255));
            c.sprite.setPosition(c.basePos.x, c.basePos.y - 20);
            _picked.push_back(c.index);
        }
        return;
    }

    
}

void HandUI::draw(RenderWindow* win)
{
    for (auto& c : _slots)
        win->draw(c.sprite);

    win->draw(_btnConfirm);
    win->draw(_txtConfirm);
}

bool HandUI::isConfirmed() const { return _confirmed; }
std::vector<int> HandUI::getPicked() const { return _picked; }
void HandUI::clearPick()
{
    _picked.clear();
    _confirmed = false;

    for (auto& c : _slots)
    {
        c.selected = false;
        c.sprite.setColor(sf::Color::White);
        c.sprite.setPosition(c.basePos);
    }
}

