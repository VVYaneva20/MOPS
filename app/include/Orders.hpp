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
private:
	static Orders* instance;
	GameManager* gameManager = GameManager::GetInstance();
	Texture2D background = LoadTexture((gameManager->GetAssetPath() + "Orders/Orders.png").c_str());
	Texture2D OrderRect = LoadTexture((gameManager->GetAssetPath() + "Orders/OrderRect.png").c_str());
	Texture2D ViewButton = LoadTexture((gameManager->GetAssetPath() + "Orders/View.png").c_str());
	Texture2D ViewButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/ViewHover.png").c_str());
	Texture2D AcceptButton = LoadTexture((gameManager->GetAssetPath() + "Orders/Accept.png").c_str());
	Texture2D AcceptButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/AcceptHover.png").c_str());
	Texture2D DeclineButton = LoadTexture((gameManager->GetAssetPath() + "Orders/Decline.png").c_str());
	Texture2D DeclineButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/DeclineHover.png").c_str());

	Texture2D Buyer = LoadTexture((gameManager->GetAssetPath() + "Orders/Buyer.png").c_str());
	std::vector<Order> orders;
	Order selectedOrder;
	void DrawOrders();
	void DisplayInfo();
	Orders();
};