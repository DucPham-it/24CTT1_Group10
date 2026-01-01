#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>

using namespace std;
using namespace sf;

#define RM_GI ResourceManager::getInstance()

class ResourceManager {
public:
	static ResourceManager* getInstance();

	Music* getMusic(string music_fileName);
	Texture* getTexture(string texture_fileName);
	Font* getFont(string font_fileName);
	Sound* getSound(string sound_fileName);

	Sound* getClickSound();
	Sound* getMovedIntoSpriteSound();
	Music* getBackgroundMusic();
	Music* getWinMusic();

	float getBMVolume();
	float getWMVolume();
	float getCSVolume();
	float getMISSVolume();

	void setBGMVolume(float);
	void setWMVolume(float);
	void setCSVolume(float);
	void setMISSVolume(float);
	
	~ResourceManager();

private:

	ResourceManager();

	static ResourceManager* m_Instance;

	float m_BackgroundVolume, m_WinVolume, m_ClickVolume, m_MovedIntoSpriteVolume;

	Music* m_BackgroundMusic, * m_WinMusic;
	Sound* m_ClickSound, * m_MovedIntoSpriteSound;
};