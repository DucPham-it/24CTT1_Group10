#pragma once
#include "./GameManager/StateManager.h"
#include "./GameManager/ResourceManager.h"
#include "./GameManager/WindowManager.h"

class Application {
public:
	void Run();
	~Application();
private:
	void Init();
	void Update();
	void Handle(Event event);
	void Render();
private:
	RenderWindow* m_Window;
};