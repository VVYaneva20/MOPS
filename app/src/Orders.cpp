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
	UnloadTexture(this->ViewButton);
	UnloadTexture(this->ViewButtonHover);
	UnloadTexture(this->AcceptButton);
	UnloadTexture(this->AcceptButtonHover);
	UnloadTexture(this->AcceptButtonLocked);
	UnloadTexture(this->DeclineButton);
	UnloadTexture(this->DeclineButtonHover);
	UnloadTexture(this->Buyer);
	UnloadTexture(this->DiscardButton);
	UnloadTexture(this->DiscardButtonHover);
}

void Orders::Update() {
	DrawTexture(this->background, 0, 0, WHITE);
	DrawOrders();
	DisplayInfo();
}

void Orders::GenerateOrder() {
	if (this->orders.size() >= 5) return;
	Json::Value root;
	std::ifstream file(gameManager->GetAssetPath() + "buyers.json");
	Order order;
	file >> root;

	Json::Value Reactions;
	std::ifstream fileReactions(gameManager->GetAssetPath() + "reactions.json");
	fileReactions >> Reactions;
	std::chrono::seconds duration(1);
	std::chrono::steady_clock::time_point endTime = this->startTime + duration;

	if (std::chrono::steady_clock::now() >= endTime) {
		this->startTime = std::chrono::steady_clock::now();
		int randReaction = GetRandomValue(0, Reactions["reactions"].size() - 1);
		Json::Value Reaction = Reactions["reactions"][randReaction];
		order.buyer = root["names"][GetRandomValue(0, root["names"].size() - 1)].asCString();
		order.formula = Reaction["product"].asCString();
		order.product = Reaction["product_name"].asCString();
		order.status = "Pending";
		order.price = std::floor(GetRandomValue(900, 1600));
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
	fileReactions.close();
	file.close();
}

void Orders::DrawOrders()
{
	for (int i = 0; i < this->orders.size(); i++)
	{
		DrawTexture(this->OrderRect, 0, 350 + (i * OrderRect.height), WHITE);
		DrawTextEx(gameManager->ArialBold, this->orders[i].product.c_str(), { 153 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].product.c_str(), 30, 1).x / 2), (float)400 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(gameManager->ArialBold, this->orders[i].formula.c_str(), { 445 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].formula.c_str(), 30, 1).x / 2), (float)400 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(gameManager->ArialBold, this->orders[i].buyer.substr(0, orders[i].buyer.find(" ")).c_str(), { 694 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].buyer.substr(0, orders[i].buyer.find(" ")).c_str(), 30, 1).x / 2), (float)400 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(gameManager->ArialBold, (std::to_string(this->orders[i].price) + "$").c_str(), { 920 - (MeasureTextEx(gameManager->ArialBold, (std::to_string(this->orders[i].price) + "$").c_str(), 30, 1).x / 2), (float)400 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTextEx(gameManager->ArialBold, this->orders[i].status.c_str(), { 1146 - (MeasureTextEx(gameManager->ArialBold, this->orders[i].status.c_str(), 30, 1).x / 2), (float)400 + (i * OrderRect.height) + 10 }, 30, 1, WHITE);
		DrawTexture(this->ViewButton, 1297, 394 + (i * OrderRect.height), WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), { 1297, (float)394 + (i * OrderRect.height), (float)ViewButton.width, (float)ViewButton.height }))
		{
			DrawTexture(this->ViewButtonHover, 1297, 394 + (i * OrderRect.height), WHITE);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				this->selectedOrder = orders[i];
			}
		}
	}
}

void Orders::DisplayInfo()
{
	if (!selectedOrder.product.empty() && selectedOrder.status != "Declined")
	{
		DrawTexture(this->Buyer, 1467, 144, WHITE);
		DrawTextEx(gameManager->ArialBold, this->selectedOrder.buyer.c_str(), { 1600, (float)144 + (Buyer.height / 2) - 15 }, 30, 1, WHITE);
		DrawTexture(this->selectedOrder.status == "Accepted" ? this->DiscardButton : this->DeclineButton, 1462, 974, WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), { 1462, 974, (float)AcceptButton.width, (float)AcceptButton.height }))
		{
			DrawTexture(this->selectedOrder.status == "Accepted" ? this->DiscardButtonHover : this->DeclineButtonHover, 1462, 974, WHITE);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				selectedOrder.status = "Declined";
				for (size_t i = 0; i < this->orders.size(); i++)
				{
					if (this->orders[i].buyer == selectedOrder.buyer)
					{
						if (orders[i].status == "Accepted") this->m_Accepted = false;
						this->orders.erase(this->orders.begin() + i);
						break;
					}
				}
			}
		}

		DrawTexture(this->m_Accepted ? this->AcceptButtonLocked : this->AcceptButton, 1701, 974, WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), { 1701, 974, (float)DeclineButton.width, (float)DeclineButton.height }) && !this->m_Accepted)
		{
			DrawTexture(this->AcceptButtonHover, 1701, 974, WHITE);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{

				for (size_t i = 0; i < this->orders.size(); i++) {
					if (this->orders[i].buyer == selectedOrder.buyer && this->orders[i].product == selectedOrder.product)
					{
						this->m_Accepted = true;
						this->orders[i].status = "Accepted";

					}
				}
				selectedOrder.status = "Accepted";
				this->m_currentOrder = selectedOrder;
			}
		}

	}
}

Orders::Order Orders::GetCurrentOrder() {
	if (!this->m_Accepted) return {};
	return this->m_currentOrder;
}

void Orders::FinishOrder()
{
	for (size_t i = 0; i < this->orders.size(); i++)
	{
		if (this->orders[i].buyer == selectedOrder.buyer && this->orders[i].product == selectedOrder.product)
		{
			this->orders.erase(this->orders.begin() + i);
			break;
		}
	}
	this->m_Accepted = false;
	this->m_currentOrder = {};
}