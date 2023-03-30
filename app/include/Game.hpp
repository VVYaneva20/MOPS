#pragma once
#include <GameManager.hpp>
#include <SiteHome.hpp>
#include <Menu.hpp>
#include <raymath.h>
#include <Orders.hpp>
#include <iostream>

class Game {
public:
	Game();
	~Game();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Orders* orders = new Orders();
	Texture2D HUD = LoadTexture((gameManager->GetAssetPath() + "Lab/HUD.png").c_str());
	bool isInventoryOpen = false;
	void Update();
	bool selected = false;
};