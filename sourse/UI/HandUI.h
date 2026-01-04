#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../GameObject/Card/Card.h"
#include "../GameManager/ResourceManager.h"
#include "../GameManager/SoundManager.h"
#include "../GameManager/WindowManager.h"


class HandUI {
public:
    void init(sf::Font* font, float screenW, float screenH);

    void setHand(std::vector<std::unique_ptr<Card>>& cards);

    void handleEvent(sf::Event& e);
    void draw(sf::RenderWindow* win);

    bool isConfirmed() const;
    std::vector<int> getPicked() const;
    void clearPick();

private:
    struct CardSlot {
        int index;
        bool selected = false;
        sf::Sprite sprite;
        sf::Vector2f basePos;
    };

    std::vector<CardSlot> _slots;
    std::vector<int> _picked;

    sf::Vector2f _origin;
    float _spacing = 120.f;

    sf::RectangleShape _btnConfirm;
    sf::Text _txtConfirm;

    bool _confirmed = false;

    float DESIGN_W;
    float DESIGN_H;

    float sx;
    float sy;
};
