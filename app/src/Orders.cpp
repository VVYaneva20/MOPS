#include <Orders.hpp>

Orders* Orders::instance;

Orders* Orders::GetInstance() {
	if (!instance) instance = new Orders();
	return instance;
}

Orders::Orders() {
	Json::Value root;
	std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
	file >> root;
	file.close();
	for (int i = 0; i < root["orders"].size(); i++) {
		Order order;
		order.product = root["orders"][i]["product"].asCString();
		order.formula = root["orders"][i]["formula"].asCString();
		order.status = root["orders"][i]["status"].asCString();
		order.buyer = root["orders"][i]["buyer"].asCString();
		order.price = root["orders"][i]["price"].asInt();
		for (int j = 0; j < root["orders"][i]["reactants"].size(); j++) {
			Reactants reactant;
			reactant.name = root["orders"][i]["reactants"][j]["name"].asCString();
			reactant.quantity = root["orders"][i]["reactants"][j]["quantity"].asInt();
			order.reactants.push_back(reactant);
		}
		this->orders.push_back(order);
		if (this->orders[i].status == "Accepted")
		{
			this->m_currentOrder = this->orders[i];
			this->m_Accepted = true;
		}
		
	}
}

Orders::~Orders() {
	UnloadTextures();
	Json::Value root;
	std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
	file >> root;
	file.close();
	Json::Value orderArray(Json::arrayValue);
	for (int i = 0; i < this->orders.size(); i++) {
		if (this->orders[i].status == "Accepted" || this->orders[i].status == "Pending")
		{
			Json::Value order(Json::objectValue);
			order["product"] = this->orders[i].product.c_str();
			order["formula"] = this->orders[i].formula.c_str();
			order["status"] = this->orders[i].status.c_str();
			order["buyer"] = this->orders[i].buyer.c_str();
			order["price"] = this->orders[i].price;
			Json::Value reactantArray(Json::arrayValue);
			for (int j = 0; j < this->orders[i].reactants.size(); j++) {
				Json::Value reactant;
				reactant["name"] = this->orders[i].reactants[j].name.c_str();
				reactant["quantity"] = this->orders[i].reactants[j].quantity;
				reactantArray.append(reactant);
			}
			order["reactants"] = reactantArray;
			orderArray.append(order);
		}
	}
	root["orders"] = orderArray;
	std::ofstream file2(gameManager->GetAssetPath() + "savedata.json");
	file2 << root;
	file2.close();
}

void Orders::Update() {
	DrawTexture(this->background, 0, 0, WHITE);
	DrawOrders();
	DisplayInfo();
}

void Orders::Reinitialize()
{
	UnloadTextures();
	this->background = LoadTexture((gameManager->GetAssetPath(true) + "Orders/Orders.png").c_str());
	this->OrderRect = LoadTexture((gameManager->GetAssetPath(true) + "Orders/OrderRect.png").c_str());
	this->ViewButton = LoadTexture((gameManager->GetAssetPath() + "Orders/View.png").c_str());
	this->ViewButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/ViewHover.png").c_str());
	this->AcceptButton = LoadTexture((gameManager->GetAssetPath() + "Orders/Accept.png").c_str());
	this->AcceptButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/AcceptHover.png").c_str());
	this->AcceptButtonLocked = LoadTexture((gameManager->GetAssetPath() + "Orders/AcceptLocked.png").c_str());
	this->DeclineButton = LoadTexture((gameManager->GetAssetPath() + "Orders/Decline.png").c_str());
	this->DeclineButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/DeclineHover.png").c_str());
	this->DiscardButton = LoadTexture((gameManager->GetAssetPath() + "Orders/Discard.png").c_str());
	this->DiscardButtonHover = LoadTexture((gameManager->GetAssetPath() + "Orders/DiscardHover.png").c_str());
	this->Buyer = LoadTexture((gameManager->GetAssetPath(true) + "Orders/Buyer.png").c_str());
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
	std::chrono::seconds duration(gameManager->OrderFrequencyUpgrade ? 30 : 1);
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
		std::string ProductName = selectedOrder.product;
		for (size_t i = 0; i < ProductName.length(); i++) if (ProductName[i] == ' ') ProductName[i] = '\n';
		DrawTextEx(gameManager->ArialBold, ("Product: " + ProductName).c_str(), {1500, 300}, 40, 2, WHITE);
		DrawTextEx(gameManager->ArialBold, ("Formula: " + selectedOrder.formula).c_str(), {1500, 450}, 40, 2, WHITE);
		DrawTextEx(gameManager->ArialBold, ("Total: " + std::to_string(selectedOrder.price) + "$").c_str(), { 1500, 600 }, 40, 2, WHITE);
		DrawTextEx(gameManager->ArialBold, ("Status: " + selectedOrder.status).c_str(), { 1500, 750 }, 40, 2, WHITE);
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

void Orders::UnloadTextures()
{
	UnloadTexture(this->background);
	UnloadTexture(this->OrderRect);
	UnloadTexture(this->ViewButton);
	UnloadTexture(this->ViewButtonHover);
	UnloadTexture(this->AcceptButton);
	UnloadTexture(this->AcceptButtonHover);
	UnloadTexture(this->AcceptButtonLocked);
	UnloadTexture(this->DeclineButton);
	UnloadTexture(this->DeclineButtonHover);
	UnloadTexture(this->DiscardButton);
	UnloadTexture(this->DiscardButtonHover);
	UnloadTexture(this->Buyer);
}