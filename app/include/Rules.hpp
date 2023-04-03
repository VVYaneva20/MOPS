#pragma once
#include <GameManager.hpp>
#include <Game.hpp>

class Rules {
public:
	Rules();
	~Rules();
private:
	GameManager* gameManager = GameManager::GetInstance();
	
	std::vector<std::string> m_ButtonsLight = { "Rules/Next.png", "Rules/Back.png" };
	std::vector<std::string> m_ButtonsHoverLight = { "Rules/NextHover.png", "Rules/BackHover.png" };
	std::vector<std::string> m_ButtonsDark = { "Rules/NextDark.png", "Rules/BackDark.png" };
	std::vector<std::string> m_ButtonsHoverDark = { "Rules/NextDarkHover.png", "Rules/BackDarkHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {1320, 812}, {313, 812} };
	std::vector<std::string> m_ButtonNames = { "NEXT", "BACK" };
};

class SecondPage {
public:
	SecondPage();
	~SecondPage();
private:
	GameManager* gameManager = GameManager::GetInstance();
	std::vector<std::string> m_ButtonsLight = { "Rules/Back.png" };
	std::vector<std::string> m_ButtonsHoverLight = { "Rules/BackHover.png" };
	std::vector<std::string> m_ButtonsDark = { "Rules/BackDark.png" };
	std::vector<std::string> m_ButtonsHoverDark = { "Rules/BackDarkHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {313, 812} };
	std::vector<std::string> m_ButtonNames = { "BACK" };
};