#include "WindowManager.h"

WindowManager* WindowManager::m_Instance = nullptr;

WindowManager::WindowManager()
{
	VideoMode desktopSize = VideoMode::getDesktopMode();
	WIDTH_SCREEN = desktopSize.width;
	HEIGHT_SCREEN = desktopSize.height;
}
WindowManager::~WindowManager()
{
	delete m_Instance;
}

WindowManager* WindowManager::getInstance()
{
	if (m_Instance == nullptr) {
		m_Instance = new WindowManager();
	}
	return m_Instance;
}

unsigned int WindowManager::getWidthScreen()
{
	return WIDTH_SCREEN;
}

unsigned int WindowManager::getHeightScreen()
{
	return HEIGHT_SCREEN;
}

float WindowManager::getScaleX()
{
	return WIDTH_SCREEN / 1366.f;
}

float WindowManager::getScaleY()
{
	return HEIGHT_SCREEN / 768.f;
}
