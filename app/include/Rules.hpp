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
	std::vector<Vector2> m_ButtonPositions = { {1320, 781}, {314, 781} };
	std::vector<std::string> m_ButtonNames = { "NEXT", "BACK" };
};