#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "../GameManager/StateManager.h"

using namespace std;
using namespace sf;

class StateMenu : public State {
private:
	bool m_IsMoveIntoButton;

	vector<Sprite> m_SpriteList;

	bool isMovedIntoButton(unsigned int x, unsigned int y);

	unsigned int m_PositionMouseX, m_PositionMouseY;

public:

	StateMenu();
	~StateMenu();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Handle(Event event);
	void Render(RenderWindow* window);
};
