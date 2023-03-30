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
	int getBalance();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Orders* orders = new Orders();
	Texture2D HUD = LoadTexture((gameManager->GetAssetPath() + "Lab/HUD.png").c_str());
	void Update();
	void DrawInventory();
	bool selected = false;
	bool isInventoryOpen = false;
	int balance = 500;
};