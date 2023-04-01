#pragma once
#include <GameManager.hpp>
#include <chrono>
#include <json.h>
#include <string>
#include <vector>
#include <fstream>
class Orders {
public:
	Orders();
	~Orders();
	void Update();

	struct Reactants {
		std::string name;
		int quantity;
	};
	struct Order {
		std::string product;
		std::vector<Reactants> formula;
		std::string status;
		std::string buyer;
		std::string date;
		float price;
	};
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	Order generateOrder();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Texture2D background = LoadTexture((gameManager->GetAssetPath() + "Orders/Orders.png").c_str());
	std::vector<Order> orders;
};