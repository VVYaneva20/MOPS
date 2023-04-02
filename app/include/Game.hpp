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
		bool holding = false;
	};
	GameManager* gameManager = GameManager::GetInstance();
	Orders* orders = Orders::GetInstance();
	Texture2D HUD = LoadTexture((gameManager->GetAssetPath() + "Lab/HUD.png").c_str());
	Texture2D Slot = LoadTexture((gameManager->GetAssetPath() + "Lab/InventorySlot.png").c_str());
	Texture2D SlotHover = LoadTexture((gameManager->GetAssetPath() + "Lab/InventorySlotHover.png").c_str());
	Texture2D Prev = LoadTexture((gameManager->GetAssetPath() + "Lab/Prev.png").c_str());
	Texture2D PrevHover = LoadTexture((gameManager->GetAssetPath() + "Lab/PrevHover.png").c_str());
	Texture2D Next = LoadTexture((gameManager->GetAssetPath() + "Lab/Next.png").c_str());
	Texture2D NextHover = LoadTexture((gameManager->GetAssetPath() + "Lab/NextHover.png").c_str());
	Texture2D Flask = LoadTexture((gameManager->GetAssetPath() + "Lab/Flask.png").c_str());
	Texture2D BigFlask = LoadTexture((gameManager->GetAssetPath() + "Lab/BigFlask.png").c_str());
	Texture2D BigFlaskHover = LoadTexture((gameManager->GetAssetPath() + "Lab/BigFlaskHover.png").c_str());
	std::vector<InventorySlot> inventory;
	std::vector<InventorySlot> tableElements;
	std::vector<InventorySlot> BowlElements;
	void Update();
	void SetInventory();
	void DrawInventory();
	void DrawOrder();
	void DrawTable();
	void MixReactions(InventorySlot &el);
	bool IsReactionReady();
	Orders::Order order;
	bool holding = false;
	bool isInventoryOpen = false;
	int m_Balance = gameManager->GetBalance();
	int page = 1;
};