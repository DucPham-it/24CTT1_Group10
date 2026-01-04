#pragma once

#include "../GameManager/WindowManager.h"
#include <SFML/Graphics.hpp>
#include <string>

class EnergyInputUI {
public:
    void init(sf::Font* font, float W, float H);

    void handleEvent(sf::Event& e);
    void handleMouse(sf::Vector2f mouse);

    void draw(sf::RenderWindow* window);

    void forceConfirm();
    bool isConfirmed() const;
    void resetConfirm();

    int getAtk() const;
    int getDef() const;
    int getJP() const;

    void clear();

private:
    struct InputBox {
        sf::RectangleShape box;
        sf::Text text;
        std::string value;
        bool active = false;

        void handleEvent(sf::Event& e);
        int  getInt() const;
        void clear();
    };

    float DESIGN_W;
    float DESIGN_H;

    float sx;
    float sy;

    InputBox atkBox, defBox, jpBox;

    sf::RectangleShape btnConfirm;
    sf::Text txtConfirm;

    sf::Text txtHint;
    sf::Text txtAtk, txtDef, txtJP;

    int _focus = 0;
    bool _confirmed = false;

    void updateFocus();
};
