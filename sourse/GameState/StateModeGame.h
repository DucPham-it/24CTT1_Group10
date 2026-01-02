#pragma once

#include "State.h"
#include "../GameState/StateNewGame.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class StateModeGame : public State {
public:
	StateModeGame();
	~StateModeGame();

	void Init() override;
	void Handle(Event event) override;
	void Render(RenderWindow* window) override;

	void Exit() override;
	void Pause() override;
	void Resume() override;

private:
	vector<Sprite> m_ListSprite;

	bool isMovedIntoButton(unsigned int x, unsigned int y);

	unsigned int m_PositionMouseX, m_PositionMouseY;

	bool m_IsMoveIntoButton;
};
