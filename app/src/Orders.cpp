#include <Orders.hpp>

Orders* Orders::instance;

Orders* Orders::GetInstance() {
	if (!instance) instance = new Orders();
	return instance;
}

Orders::Orders() {}

Orders::~Orders() {
	UnloadTexture(this->background);
	UnloadTexture(this->OrderRect);
}

void Orders::Update() {
	DrawTexture(this->background, 0, 0, WHITE);
	DrawOrders();
}

void Orders::generateOrder() {
	if (this->orders.size() >= 5) return;
	Json::Value root;
	std::ifstream file(this->gameManager->GetAssetPath() + "buyers.json");
	Order order;
	file >> root;

	Json::Value Reactions;
	std::ifstream fileReactions(this->gameManager->GetAssetPath() + "reactions.json");
	fileReactions >> Reactions;
	std::chrono::seconds duration(10);
	std::chrono::steady_clock::time_point endTime = this->startTime + duration;

	if (std::chrono::steady_clock::now() >= endTime) {
		this->startTime = std::chrono::steady_clock::now();
		int randReaction = GetRandomValue(0, Reactions["reactions"].size() - 1);
		Json::Value Reaction = Reactions["reactions"][randReaction];
		order.buyer = root["names"][GetRandomValue(0, root["names"].size() - 1)].asCString();
		order.formula = Reaction["product"].asCString();
		order.product = Reaction["product_name"].asCString();
		order.status = "Pending";
		for (int i = 0; i < Reaction["reactants"].size(); i++) {
			Reactants reactant;
			reactant.name = Reaction["reactants"][i]["name"].asCString();
			reactant.quantity = Reaction["reactants"][i]["quantity"].asInt();
			order.reactants.push_back(reactant);
		}
		endTime = this->startTime + duration;
		std::cout << "Order generated" << std::endl;
		this->orders.push_back(order);
	}
}

void Orders::DrawOrders()
{
	for (int i = 0; i < this->orders.size(); i++)
	{
		DrawTexture(this->OrderRect, 0, 350 + (i * OrderRect.height), WHITE);
		DrawTextEx(this->gameManager->ArialBold, this->orders[i].product.c_str(), { 153 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].product.c_str(), 30, 1).x / 2), (float)390 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(this->gameManager->ArialBold, this->orders[i].formula.c_str(), { 445 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].formula.c_str(), 30, 1).x / 2), (float)390 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(this->gameManager->ArialBold, this->orders[i].buyer.c_str(), { 694 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].buyer.c_str(), 30, 1).x / 2), (float)390 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		//DrawTextEx(this->gameManager->ArialBold, this->orders[i].total.c_str(), { 943 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].total.c_str(), 30, 1).x / 2), (float)390 * (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(this->gameManager->ArialBold, this->orders[i].status.c_str(), { 1146 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].status.c_str(), 30, 1).x / 2), (float)390 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
	}
}