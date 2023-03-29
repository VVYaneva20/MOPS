#pragma once
#include <GameManager.hpp>

class Orders {
public:
	Orders();
	~Orders();
	void Update();
private:
	GameManager* gameManager = GameManager::GetInstance();
	
	struct Order {
		std::string formula;
		std::string product;
		std::string status;
		std::string buyer;
		std::string date;
		float price;
	};
};