#pragma once
#include "../GameManager/ResourceManager.h"
#include "../GameManager/StateManager.h"


class State {
public:
	State() {}
	virtual ~State() {}

	virtual void Exit() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Init() = 0;
	virtual void Handle(Event event) = 0;
	virtual void Render(RenderWindow* window) = 0;

	static State* CreateState(unsigned int state);
};

