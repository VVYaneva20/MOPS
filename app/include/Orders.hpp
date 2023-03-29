#pragma once
#include <GameManager.hpp>

class Orders {
public:
	Orders();
	~Orders();
	void Update();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Texture2D background = LoadTexture((gameManager->GetAssetPath() + "Orders/Orders.png").c_str());
	struct Order {
		std::string formula;
		std::string product;
		std::string status;
		std::string buyer;
		std::string date;
		float price;
	};
};