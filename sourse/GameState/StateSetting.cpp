#include "StateSetting.h"

StateSetting::StateSetting()
{
	m_ListSprite.resize(16);
	m_ListText.resize(4);

	m_Volumn.resize(4);
	m_Volumn[0] = RM_GI->getBMVolume();
	m_Volumn[1] = RM_GI->getWMVolume();
	m_Volumn[2] = RM_GI->getCSVolume();
	m_Volumn[3] = RM_GI->getMISSVolume();

	m_KnobDragging = 0;
	m_MousePos = 0.f;
}

StateSetting::~StateSetting()
{
}

void StateSetting::Exit()
{
}

void StateSetting::Pause()
{
}

void StateSetting::Resume()
{
}

void StateSetting::Init()
{
	Font* font = RM_GI->getFont("NotoSansSC-VariableFont_wght.ttf");

	Texture* texture;

	vector<string> texturePath = {
		"background.png", "ui.png", "title-settings.png",

		"hoveredbutton-settings-music.png",

		"slider-bar.png", "progress-bar.png", "slider-knob.png",// BG Music

		"slider-bar.png", "progress-bar.png", "slider-knob.png",// Game Over Music

		"slider-bar.png", "progress-bar.png", "slider-knob.png",// CLick sound

		"slider-bar.png", "progress-bar.png", "slider-knob.png"// Hover sound
	};
	vector<Vector2f> texturePos = {
		{0.f, 0.f}, {320.f * WM_GI->getScaleX(), 50.f * WM_GI->getScaleY()}, {500 * WM_GI->getScaleX(), 120 * WM_GI->getScaleY()},
		{370.f * WM_GI->getScaleX(), 195.f * WM_GI->getScaleY()},

		{650.f * WM_GI->getScaleX(), 265.f * WM_GI->getScaleY()}, {650.f * WM_GI->getScaleX(), 265.f * WM_GI->getScaleY()},
		{static_cast<float>(2.325 * m_Volumn[0] + 650) * WM_GI->getScaleX(), 260.f * WM_GI->getScaleY()},

		{650.f * WM_GI->getScaleX(), 305.f * WM_GI->getScaleY()}, {650.f * WM_GI->getScaleX(), 305.f * WM_GI->getScaleY()},
		{static_cast<float>(2.325 * m_Volumn[1] + 650) * WM_GI->getScaleX(), 300.f * WM_GI->getScaleY()},

		{650.f * WM_GI->getScaleX(), 345.f * WM_GI->getScaleY()}, {650.f * WM_GI->getScaleX(), 345.f * WM_GI->getScaleY()},
		{static_cast<float>(2.325 * m_Volumn[2] + 650) * WM_GI->getScaleX(), 340.f * WM_GI->getScaleY()},

		{650.f * WM_GI->getScaleX(), 385.f * WM_GI->getScaleY()}, {650.f * WM_GI->getScaleX(), 385.f * WM_GI->getScaleY()},
		{static_cast<float>(2.325 * m_Volumn[3] + 650) * WM_GI->getScaleX(), 380.f * WM_GI->getScaleY()}

	};
	vector<Vector2f> textureScale = {
		{WM_GI->getWidthScreen() / 1301.f, WM_GI->getHeightScreen() / 989.f}, {470.f * WM_GI->getScaleX() / 187.f, WM_GI->getHeightScreen() / 490.f},
		{5.f * WM_GI->getScaleX(), 5.f * WM_GI->getScaleY()},
		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},

		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()}, {static_cast<float>(2.325 * m_Volumn[0] + 8.75) / 100.f * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},
		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},

		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()}, {static_cast<float>(2.325 * m_Volumn[1] + 8.75) / 100.f * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},
		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},

		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()}, {static_cast<float>(2.325 * m_Volumn[2] + 8.75) / 100.f * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},
		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},

		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()}, {static_cast<float>(2.325 * m_Volumn[3] + 8.75) / 100.f * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},
		{(float)2.5 * WM_GI->getScaleX(), (float)2.5 * WM_GI->getScaleY()},

	};
	for (size_t i = 0; i < texturePath.size(); i++) {
		texture = RM_GI->getTexture(texturePath[i]);
		m_ListSprite[i].setTexture(*texture);
		m_ListSprite[i].setPosition(texturePos[i]);
		m_ListSprite[i].setScale(textureScale[i]);
	};

	vector<string> textString = { "Background music", "Game over music", "Click sound", "Hover sound" };
	vector<Vector2f> textPos = {
		{370.f * WM_GI->getScaleX(), 260.f * WM_GI->getScaleY()}, {370.f * WM_GI->getScaleX(), 300.f * WM_GI->getScaleY()},
		{370.f * WM_GI->getScaleX(), 340.f * WM_GI->getScaleY()}, {370.f * WM_GI->getScaleX(), 380.f * WM_GI->getScaleY()}
	};
	for (size_t i = 0; i < textString.size(); i++) {
		m_ListText[i].setFont(*font);
		m_ListText[i].setString(textString[i]);
		m_ListText[i].setFillColor(Color::Black);
		m_ListText[i].setCharacterSize(20);
		m_ListText[i].setPosition(textPos[i]);
	}
}

void StateSetting::Handle(Event event)
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
		StateManager::getInstance()->ChangeState(0);
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && m_KnobDragging == 0) {
		for (size_t i = 6; i < 16; i += 3) {
			if (m_ListSprite[i].getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
			{
				m_KnobDragging = i;
			}
		}
	}
	else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		m_KnobDragging = 0;
	}
	if (event.type == Event::MouseMoved && m_KnobDragging) {
		m_MousePos = static_cast<float>(event.mouseMove.x);
		setVolumn();
	}
}

void StateSetting::Render(RenderWindow* window)
{
	for (size_t i = 0; i < m_ListSprite.size(); i++) window->draw(m_ListSprite[i]);
	for (size_t i = 0; i < 4; i++) window->draw(m_ListText[i]);
}

void StateSetting::setVolumn()
{
	int stt = m_KnobDragging / 3 - 2;

	float sliderLeft = 650.f * WM_GI->getScaleX();
	float sliderRight = 882.5f * WM_GI->getScaleX();
	float sliderWidth = sliderRight - sliderLeft;

	// Clamp chuột trong vùng slider
	float x = std::max(sliderLeft, std::min(m_MousePos, sliderRight));

	// Di chuyển knob
	m_ListSprite[m_KnobDragging].setPosition({
		x,
		(260.f + stt * 40.f) * WM_GI->getScaleY()
		});

	// Tính volume 0 → 100
	float volume = (x - sliderLeft) / sliderWidth * 100.f;

	// Scale progress bar
	float percent = volume / 100.f;

	m_ListSprite[m_KnobDragging - 1].setScale({
		percent * 2.5f * WM_GI->getScaleX(),
		2.5f * WM_GI->getScaleY()
		});

	// Set audio
	switch (m_KnobDragging) {
	case 6:  RM_GI->setBGMVolume(volume);  break;
	case 9:  RM_GI->setWMVolume(volume);   break;
	case 12: RM_GI->setCSVolume(volume);   break;
	case 15: RM_GI->setMISSVolume(volume); break;
	}
}
// void StateSetting::setVolumn() {
// 	int stt = m_KnobDragging / 3 - 2;

// 	m_ListSprite[m_KnobDragging].setPosition(Vector2f{ max(static_cast<float>(650 * WM_GI->getScaleX()), min(m_MousePos, static_cast<float>(882.5 * WM_GI->getScaleX()))),
// 														static_cast<float>(260 + stt * 40) * WM_GI->getScaleY() });
// 	float volume = (m_ListSprite[m_KnobDragging].getPosition().x - 650 * WM_GI->getScaleX()) * 100 / static_cast<float>(232.5);
// 	m_ListSprite[m_KnobDragging - 1].setScale(Vector2f{ static_cast<float>(2.325 * volume + 8.75) / 100.f,
// 		(float)2.5 * WM_GI->getScaleY() });

// 	switch (m_KnobDragging) {
// 	case 6:
// 		RM_GI->setBGMVolume(volume);
// 		SoundManager::instance().setMasterVolume(volume);
// 		break;
// 	case 9:
// 		RM_GI->setWMVolume(volume);
// 		break;
// 	case 12:
// 		RM_GI->setCSVolume(volume);
// 		break;
// 	case 15:
// 		RM_GI->setMISSVolume(volume);
// 		break;
// 	default:
// 		break;
// 	}

// }
