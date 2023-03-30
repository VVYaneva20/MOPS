#pragma once
#include <GameManager.hpp>
#include <chrono>
class Orders {
public:
	Orders();
	~Orders();
	void Update();

	struct Order {
		std::string formula;
		std::string product;
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