#pragma once
#include <GameManager.hpp>
#include <Game.hpp>

class Rules {
public:
	Rules();
	~Rules();
private:
	GameManager* gameManager = GameManager::GetInstance();
	
	std::vector<std::string> m_Buttons = { "Rules/Next.png", "Rules/Back.png" };
	std::vector<std::string> m_ButtonsHover = { "Rules/NextHover.png", "Rules/BackHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {1320, 812}, {313, 812} };
	std::vector<std::string> m_ButtonNames = { "NEXT", "BACK" };
	std::vector<bool> m_hasTheme = { true, true };
};

class SecondPage {
public:
	SecondPage();
	~SecondPage();
private:
	GameManager* gameManager = GameManager::GetInstance();
	std::vector<std::string> m_Buttons = { "Rules/Back.png" };
	std::vector<std::string> m_ButtonsHover = { "Rules/BackHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {313, 812} };
	std::vector<std::string> m_ButtonNames = { "BACK" };
	std::vector<bool> m_hasTheme = { true };
};