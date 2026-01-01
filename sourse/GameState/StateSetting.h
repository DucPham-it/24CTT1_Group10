#pragma once
#include "../GameManager/StateManager.h"
#include <vector>
#include <algorithm>

class StateSetting : public State
{
public:
	StateSetting();
	virtual ~StateSetting();

	void Exit();
	void Pause();
	void Resume();


	void Init();
	void Handle(Event event);
	void Render(RenderWindow* window);

private:
	vector<Text> m_ListText;
	vector<Sprite> m_ListSprite;
	void setVolumn();
	vector<float> m_Volumn;
	unsigned int m_KnobDragging;
	float m_MousePos;
};