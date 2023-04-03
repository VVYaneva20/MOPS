#pragma once
#include <GameManager.hpp>
#include <Game.hpp>

class Settings {
public:
	Settings();
	~Settings();
private:
	GameManager* gameManager = GameManager::GetInstance();
	void DrawSettings();
	std::vector<std::string> m_ButtonsLight = { "Settings/Back.png", "Settings/ToggleTheme.png", "Settings/CursorButton.png" };
	std::vector<std::string> m_ButtonsHoverLight = { "Settings/BackHover.png", "Settings/ToggleThemeHover.png", "Settings/CursorButtonHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {540,760}, {540, 310}, {540, 530} };
	std::vector<std::string> m_ButtonsDark = { "Settings/BackDark.png", "Settings/ToggleThemeDark.png", "Settings/CursorButtonDark.png" };
	std::vector<std::string> m_ButtonsHoverDark = { "Settings/BackDarkHover.png", "Settings/ToggleThemeHoverDark.png", "Settings/CursorButtonHoverDark.png" };
	std::vector<std::string> m_ButtonNames = { "Back", "Theme", "Cursor" };
};