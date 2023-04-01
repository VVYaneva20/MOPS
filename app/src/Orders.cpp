#include <Orders.hpp>

Orders::Orders() {}

Orders::~Orders() {
	UnloadTexture(this->background);
}

void Orders::Update() {
	DrawTexture(this->background, 0, 0, WHITE);
}

Orders::Order Orders::generateOrder() {
	Json::Value root;
	std::ifstream file(this->gameManager->GetAssetPath() + "buyers.json");
	Orders::Order order;
	file >> root;

	Json::Value Reactions;
	std::ifstream fileReactions(this->gameManager->GetAssetPath() + "reactions.json");
	fileReactions >> Reactions;
	if (this->orders.size() > 5) return {};
	std::chrono::seconds duration(10);
	std::chrono::steady_clock::time_point endTime = this->startTime + duration;

	if (std::chrono::steady_clock::now() >= endTime) {
		this->startTime = std::chrono::steady_clock::now();
		int randomReactionIndex = GetRandomValue(0, Reactions["reactions"].size() - 1);
		std::cout << randomReactionIndex << std::endl;
		order.buyer = root["names"][rand() % root["names"].size() - 1].asCString();
		order.product = Reactions["reactions"][randomReactionIndex]["product"].asCString();

		for (int i = 0; i < Reactions["reactions"][randomReactionIndex]["reactants"].size(); i++) {
			Orders::Reactants reactant;
			reactant.name = Reactions["reactions"][randomReactionIndex]["reactants"][i]["name"].asCString();
			reactant.quantity = Reactions["reactions"][randomReactionIndex]["reactants"][i]["quantity"].asInt();
			order.formula.push_back(reactant);
			std::cout << "Name: " << order.formula[i].name << " Quantity: " << order.formula[i].quantity << std::endl;
		}
		std::cout << order.buyer << std::endl;
		endTime = this->startTime + duration;
		std::cout << "Order generated" << std::endl;
	}
	return order;
}