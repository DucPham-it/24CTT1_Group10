#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "../GameObject/Card/Card.h"
#include "../GameObject/Player/Player.h"
#include "../GameManager/WindowManager.h"


class PlayedCardsView
{
public:
    void init(sf::Font* font, float W, float H);

    // State gọi sau khi player/bot chọn bài
    void setPlayedCards(
        bool isP1,
        Player* owner,
        const std::vector<int>& picked,
        const std::vector<std::unique_ptr<Card>>& hand
    );

    void draw(sf::RenderWindow* window);

private:
    std::vector<sf::Sprite> _p1Sprites;
    std::vector<sf::Sprite> _p2Sprites;

    sf::Text _txtP1;
    sf::Text _txtP2;

    float _centerY;
    float _spacing;

    float DESIGN_W;
    float DESIGN_H;

    float sx;
    float sy;
};
