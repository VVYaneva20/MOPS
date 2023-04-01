#pragma once
#include <GameManager.hpp>
#include <SiteHome.hpp>
#include <Menu.hpp>
#include <raymath.h>
#include <Orders.hpp>
#include <json.h>
#include <fstream>
#include <iostream>

class Game {
public:
	Game();
	~Game();
private:
	struct InventorySlot {
		std::string name;
		std::string symbol;
		int quantity;
	};
	GameManager* gameManager = GameManager::GetInstance();
	Orders* orders = new Orders();
	Texture2D HUD = LoadTexture((gameManager->GetAssetPath() + "Lab/HUD.png").c_str());
	Texture2D Slot = LoadTexture((gameManager->GetAssetPath() + "Lab/InventorySlot.png").c_str());
	std::vector<InventorySlot> inventory;
	void Update();
	void setInventory();
	void DrawInventory();
	bool selected = false;
	bool isInventoryOpen = false;
	int m_Balance = gameManager->GetBalance();
};