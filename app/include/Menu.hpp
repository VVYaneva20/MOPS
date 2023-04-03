#pragma once
#include <GameManager.hpp>
#include <Game.hpp>
#include <Rules.hpp>
#include <Settings.hpp>

class Menu {
public:
    Menu();
    ~Menu();
private:
    GameManager* gameManager = GameManager::GetInstance();
    Rectangle m_Rect = { GetScreenWidth() / 2.0f, -100, 150, 150 };
    Vector2 m_MousePos = GetMousePosition();
    void DrawMenu();

    const int c_ButtonWidth = 367;
    const int c_ButtonHeight = 82;

    const int c_LogoWidth = 457;
    const int c_LogoHeight = 149;

    Vector2 m_LogoPos = { GetScreenWidth() / 2.0f - this->c_LogoWidth / 2.0f, GetScreenHeight() / 2.0f - this->c_LogoHeight / 2.0f - 350 };
    std::vector<std::string> m_ImagesLight = { "Menu/Menu.png", "Menu/Logo.png" };
    std::vector<std::string> m_ImagesDark = { "Menu/DarkMenu.png", "Menu/Logo.png" };
    std::vector<std::string> m_ButtonsLight = { "Menu/Start.png", "Menu/Settings.png", "Menu/Rules.png", "Menu/Exit.png" };
    std::vector<std::string> m_ButtonsHoverLight = { "Menu/StartHover.png", "Menu/SettingsHover.png", "Menu/RulesHover.png", "Menu/ExitHover.png" };
    std::vector<Vector2> m_ButtonPositions = { {gameManager->GetScreenSize().x / 2 - this->c_ButtonWidth / 2, gameManager->GetScreenSize().y / 2 - this->c_ButtonHeight / 2 - 65}, {gameManager->GetScreenSize().x / 2 - this->c_ButtonWidth / 2, gameManager->GetScreenSize().y / 2 - this->c_ButtonHeight / 2 + 55}, {gameManager->GetScreenSize().x / 2 - this->c_ButtonWidth / 2, gameManager->GetScreenSize().y / 2 - this->c_ButtonHeight / 2 + 174}, {gameManager->GetScreenSize().x / 2 - this->c_ButtonWidth / 2, gameManager->GetScreenSize().y / 2 - this->c_ButtonHeight / 2 + 295} };
    std::vector<std::string> m_ButtonsDark = { "Menu/StartDark.png", "Menu/SettingsDark.png", "Menu/RulesDark.png", "Menu/ExitDark.png"};
    std::vector<std::string> m_ButtonsHoverDark = { "Menu/StartDarkHover.png", "Menu/SettingsDarkHover.png", "Menu/RulesDarkHover", "Menu/ExitDarkHover.png" };
	std::vector<std::string> m_ButtonNames = { "Start", "Settings", "Rules", "Exit" };
};