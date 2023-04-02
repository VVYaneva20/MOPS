#pragma once
#include <GameManager.hpp>
#include <Game.hpp>

class Settings {
public:
	enum THEME {
		THEME_LIGHT,
		THEME_DARK
	};
	Settings(THEME currentTheme);
	~Settings();
	THEME m_CurrentTheme = THEME_DARK;
private:
	GameManager* gameManager = GameManager::GetInstance();
	void DrawSettings();
	std::vector<std::string> m_Buttons = { "Settings/Back.png", "Settings/Theme.png", "Settings/CursorButton.png" };
	std::vector<std::string> m_ButtonsHover = { "Settings/BackHover.png", "Settings/ThemeHover.png", "Settings/CursorButtonHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {540,760}, {540, 310}, {540, 530} };
	std::vector<std::string> m_ButtonNames = { "Back", "Theme", "Cursor" };
};