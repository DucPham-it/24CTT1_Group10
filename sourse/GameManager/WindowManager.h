#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define WM_GI WindowManager::getInstance()

class WindowManager {
private:
	static WindowManager* m_Instance;
	unsigned int WIDTH_SCREEN, HEIGHT_SCREEN;
	WindowManager();
public:
	~WindowManager();
	static WindowManager* getInstance();
	unsigned int getWidthScreen();
	unsigned int getHeightScreen();
	float getScaleX();
	float getScaleY();
};