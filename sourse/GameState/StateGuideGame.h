#pragma once

#include "../GameManager/StateManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class StateGuideGame : public State
{
public:
    StateGuideGame();
    virtual ~StateGuideGame() = default;

    void Init() override;
    void Handle(Event event) override;
    void Render(RenderWindow* window) override;

    void Pause() override;
    void Resume() override;
    void Exit() override;

private:

    Sprite m_Background;

    Font* m_Font;

    Text m_GuideTextCol1;
    Text m_GuideTextCol2;
    Text m_GuideTextCol3;

    Text m_GuideFooter;


    float m_TextOffsetY;  
    float m_ScrollSpeed;   
    float m_MinOffsetY;   
    float m_MaxOffsetY;    
};