#include "Application.h"
#include "./GameState/State.h"

Application::~Application()
{
	if (m_Window != nullptr) delete m_Window;
}

void Application::Init()
{
	m_Window = new RenderWindow(VideoMode(WM_GI->getWidthScreen(), WM_GI->getHeightScreen()), "TOA SAT BAT DO", Style::Fullscreen);
	m_Window->setFramerateLimit(60);
	StateManager::getInstance()->ChangeState(0);
}

void Application::Handle(Event event) 
{
	StateManager::getInstance()->currentState()->Handle(event);
}

void Application::Update()
{
	if (StateManager::getInstance()->NeedToChangeState()) {
		StateManager::getInstance()->RunStateChange();
	}
}

void Application::Render()
{
	m_Window->clear(Color::White);
	StateManager::getInstance()->currentState()->Render(m_Window);
	m_Window->display();
}

void Application::Run()
{
	Init();

	while (m_Window->isOpen() && StateManager::getInstance()->IsRunning()) {

		Update();

		Event event;
		while (m_Window->pollEvent(event)) {
			Handle(event);
		}

		Render();
	}
	return;
}
