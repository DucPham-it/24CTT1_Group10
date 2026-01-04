#include "ResourceManager.h"

ResourceManager* ResourceManager::m_Instance = nullptr;

ResourceManager::ResourceManager() {
	m_BackgroundVolume = 100.f; m_WinVolume = 80.f;  m_ClickVolume = 60.f;  m_MovedIntoSpriteVolume = 40.f;
	// MUSIC
	Music* music1 = new Music();
	Music* music2 = new Music();
	Music* music3 = new Music();

	music1->openFromFile("Data/Music/backgroundmusic2.ogg");
	m_BackgroundMusic = music1;
	m_BackgroundMusic->setLoop(true);
	m_BackgroundMusic->play();

	music2->openFromFile("Data/Music/winmusic2.ogg");
	m_LoseMusic = music2;

	music3->openFromFile("Data/Music/winmusic3.ogg");
	m_WinMusic = music3;

	// SOUND
	SoundBuffer* soundBuffer1 = new SoundBuffer();
	SoundBuffer* soundBuffer2 = new SoundBuffer();
	Sound* sound1 = new Sound();
	Sound* sound2 = new Sound();

	soundBuffer1->loadFromFile("Data/SoundBuffer/click-sound1.ogg");
	sound1->setBuffer(*soundBuffer1);
	m_ClickSound = sound1;

	soundBuffer2->loadFromFile("Data/SoundBuffer/moved-into-sprite1.ogg");
	sound2->setBuffer(*soundBuffer2);
	m_MovedIntoSpriteSound = sound2;
}

ResourceManager* ResourceManager::getInstance()
{
	if (m_Instance == nullptr) {
		m_Instance = new ResourceManager();
	}
	return m_Instance;
}

Music* ResourceManager::getMusic(string music_fileName)
{
	Music* musicPtr = new Music();
	if (!musicPtr->openFromFile("Data/Music/" + music_fileName)) {
		cout << "Can not open " << music_fileName << endl;
	}
	return musicPtr;
}

Texture* ResourceManager::getTexture(string texture_fileName)
{
	Texture* texturePtr = new Texture();

	// Ưu tiên load theo thư mục Data/Texture
	string path1 = "Data/Texture/" + texture_fileName;
	if (texturePtr->loadFromFile(path1)) {
		return texturePtr;
	}

	// Fallback nếu chạy từ thư mục con (Debug / x64)
	string path2 = "Data/Texture/" + texture_fileName;
	if (texturePtr->loadFromFile(path2)) {
		return texturePtr;
	}

	cout << "[ERROR] Cannot load texture: " << texture_fileName << endl;
	delete texturePtr;
	return nullptr;
}


Font* ResourceManager::getFont(string font_fileName)
{
	Font* fontPtr = new Font();

	if (fontPtr->loadFromFile("Data/Font/" + font_fileName))
		return fontPtr;

	if (fontPtr->loadFromFile("Data/Font/" + font_fileName))
		return fontPtr;

	cout << "[ERROR] Cannot load font: " << font_fileName << endl;
	delete fontPtr;
	return nullptr;
}

Sound* ResourceManager::getSound(string sound_fileName)
{
	SoundBuffer* soundBufferPtr = new SoundBuffer();
	Sound* soundPtr = new Sound();
	if (!soundBufferPtr->loadFromFile("Data/SoundBuffer/" + sound_fileName)) {
		cout << "Can not open " << sound_fileName << ".ogg" << endl;
	}
	soundPtr->setBuffer(*soundBufferPtr);
	return soundPtr;
}

Sound* ResourceManager::getClickSound()
{
	return m_ClickSound;
}

Sound* ResourceManager::getMovedIntoSpriteSound()
{
	return m_MovedIntoSpriteSound;
}

Music* ResourceManager::getBackgroundMusic()
{
	return m_BackgroundMusic;
}

Music* ResourceManager::getWinMusic()
{
	return m_WinMusic;
}
Music* ResourceManager::getLoseMusic()
{
	return m_LoseMusic;
}
float ResourceManager::getBMVolume()
{
	return m_BackgroundMusic->getVolume();
}

float ResourceManager::getWMVolume()
{
	return m_WinMusic->getVolume();
}

float ResourceManager::getCSVolume()
{
	return m_ClickSound->getVolume();
}

float ResourceManager::getMISSVolume()
{
	return m_MovedIntoSpriteSound->getVolume();
}

void ResourceManager::setBGMVolume(float volume)
{
	m_BackgroundMusic->setVolume(volume);
}

void ResourceManager::setWMVolume(float volume)
{
	m_WinMusic->setVolume(volume);
}

void ResourceManager::setCSVolume(float volume)
{
	m_ClickSound->setVolume(volume);
}

void ResourceManager::setMISSVolume(float volume)
{
	m_MovedIntoSpriteSound->setVolume(volume);
}

ResourceManager::~ResourceManager()
{
	delete m_Instance;
	delete m_BackgroundMusic;
	delete m_WinMusic;
	delete m_LoseMusic;
	delete m_ClickSound;
	delete m_MovedIntoSpriteSound;
}