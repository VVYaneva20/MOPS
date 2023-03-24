#pragma once
#include <GameManager.hpp>
class Menu {
public:
	Menu();
	~Menu();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Rectangle m_Rect = { GetScreenWidth() / 2.0f, -100, 150, 150 };
	Vector2 m_MousePos = GetMousePosition();
	void DrawMenu();
};