#pragma once
#include <GameManager.hpp>
#include <chrono>
#include <json.h>
#include <string>
#include <vector>
#include <fstream>
class Orders {
public:
	~Orders();
	static Orders* GetInstance();
	void Update();

	struct Reactants {
		std::string name;
		int quantity;
	};
	struct Order {
		std::string product;
		std::string formula;
		std::vector<Reactants> reactants;
		std::string status;
		std::string buyer;
		float price;
	};
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	void generateOrder();
	void DrawOrders();
private:
	static Orders* instance;
	GameManager* gameManager = GameManager::GetInstance();
	Texture2D background = LoadTexture((gameManager->GetAssetPath() + "Orders/Orders.png").c_str());
	Texture2D OrderRect = LoadTexture((gameManager->GetAssetPath() + "Orders/OrderRect.png").c_str());
	std::vector<Order> orders;
	Orders();
};