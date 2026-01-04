#include "PlayedCardsView.h"
#include "../GameManager/ResourceManager.h"

using namespace sf;

void PlayedCardsView::init(Font* font, float W, float H)
{
    DESIGN_W = W;
    DESIGN_H = H;

    sx = WM_GI->getScaleX();
    sy = WM_GI->getScaleY();

    _centerY = (DESIGN_H * 0.3f) * sy;
    _spacing = 60.f * sx;

    _txtP1.setFont(*font);
    _txtP1.setCharacterSize(18 * sy);
    _txtP1.setFillColor(Color(230,230,230));
    _txtP1.setString("PLAYER 1");

    _txtP2.setFont(*font);
    _txtP2.setCharacterSize(18 * sy);
    _txtP2.setFillColor(Color(230,230,230));
    _txtP2.setString("PLAYER 2");
}
void PlayedCardsView::setPlayedCards(
    bool isP1,
    Player* owner,
    const std::vector<int>& picked,
    const std::vector<std::unique_ptr<Card>>& hand)
{
    auto& list = isP1 ? _p1Sprites : _p2Sprites;

    if ((!isP1) && (owner->isBot())){
        _txtP2.setString(owner->getName());
    }

    list.clear();

    for (int idx : picked)
    {
        if (auto tex = RM_GI->getTexture(hand[idx]->getIconPath()))
        {
            Sprite s;
            s.setTexture(*tex);
            s.setScale(0.25f * sx, 0.25f * sy);
            list.push_back(s);
        }
    }
}
void PlayedCardsView::draw(RenderWindow* window)
{

    // ===== Player 1 =====
    float startX_P1 = (DESIGN_W * 0.15f) * sx;

    for (int i = 0; i < _p1Sprites.size(); ++i)
    {
        _p1Sprites[i].setPosition(
            startX_P1 - i * _spacing,
            _centerY
        );
        window->draw(_p1Sprites[i]);
    }

    if (!_p1Sprites.empty())
    {
        _txtP1.setPosition(
            startX_P1 - 10.f * sx,
            _centerY - 100.f * sy);
        window->draw(_txtP1);
    }

    // ===== Player 2 =====
    float startX_P2 = (DESIGN_W * 0.75f) * sx;

    for (int i = 0; i < _p2Sprites.size(); ++i)
    {
        _p2Sprites[i].setPosition(
            startX_P2 + i * _spacing,
            _centerY
        );
        window->draw(_p2Sprites[i]);
    }

    if (!_p2Sprites.empty())
    {
        _txtP2.setPosition(
            startX_P2 + 20.f * sx,
            _centerY - 100.f * sy
        );
        window->draw(_txtP2);
    }
}
