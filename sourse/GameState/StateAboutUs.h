#pragma once
#include "../GameManager/StateManager.h"

class StateAboutUs : public State
{
public:
	StateAboutUs();
	virtual ~StateAboutUs();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Handle(Event event);
	void Render(RenderWindow* window);

private:
	unsigned int m_CurrentMember;
	vector<Sprite> m_ListSprite;
	vector<Texture*> m_MemberTexture;
	vector<vector<Text>> m_MemberInfor;
};