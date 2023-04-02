#include <Game.hpp>

Game::Game() {
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png", "Lab/Balance.png" }, { {0, 0}, {0,0} });
	gameManager->LoadButtons({ "Lab/PC.png", "Lab/Inventory.png" }, { "Lab/PCHover.png", "Lab/InventoryHover.png" }, { {1580, 575}, {956, 396} }, { "PC", "INVENTORY" });
	this->setInventory();
	this->Update();
}

Game::~Game() {
	UnloadTexture(this->HUD);
	UnloadTexture(this->Slot);
	UnloadTexture(this->Prev);
	UnloadTexture(this->PrevHover);
	UnloadTexture(this->Next);
	UnloadTexture(this->NextHover);
}

void Game::Update()
{
	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLUE);
		orders->generateOrder();
		gameManager->Update();
		this->DrawInventory();
		this->DrawOrder();
		this->m_Balance = gameManager->GetBalance();
		DrawTextEx(gameManager->ArialBold, (std::to_string(m_Balance) + "$").c_str(), { 70, 5 }, 60, 1, WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), { 1500, 300, 60, 60 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			selected = true;
		}
		if (!selected) {
			DrawRectangle(1500, 300, 60, 60, RED);
		}

		if (selected)
		{
			DrawRectangle(GetMousePosition().x - 30, GetMousePosition().y - 30, 60, 60, RED);
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				selected = false;
			}
		}
		if ((gameManager->IsButtonClicked("INVENTORY") || IsKeyPressed(KEY_I)) && !isInventoryOpen)
		{
			isInventoryOpen = true;
			gameManager->LoadButtons({ "Lab/Close.png" }, { "Lab/CloseHover.png" }, { { 1516, 140 } }, { "CLOSE" });
			continue;
		}
		EndDrawing();
		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (gameManager->IsButtonClicked("PC") && !isInventoryOpen)
		{
			SiteHome* siteHome = new SiteHome();
			delete this;
			break;
		}
	}
}

void Game::setInventory() {
	Json::Value root;
	std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
	file >> root;

	for (int i = 0; i < root["inventory"].size(); i++) {
		InventorySlot slot;
		slot.name = root["inventory"][i]["name"].asCString();
		slot.symbol = root["inventory"][i]["symbol"].asCString();
		slot.quantity = root["inventory"][i]["quantity"].asInt();
		this->inventory.push_back(slot);
	}

	file.close();
}

void Game::DrawInventory()
{
	if (isInventoryOpen) {
		DrawTexture(this->HUD, 335, 140, WHITE);
		int pages = int(25 / 24) + 1;
		if (page > 1 && page < int(this->inventory.size() / 25) + 1)
		{
			DrawTexture(this->Prev, 340, 545, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), { 340, 545, (float)this->Prev.width, (float)this->Prev.height }))
			{
				DrawTexture(this->PrevHover, 340, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page--;
			}
			DrawTexture(this->Next, 1525, 545, WHITE);
			if(CheckCollisionPointRec(GetMousePosition(), { 1521, 545, (float)this->Next.width, (float)this->Next.height }))
			{
				DrawTexture(this->NextHover, 1525, 545, WHITE);
				if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page++;
			}
		}
		if (page == 1 && (int(this->inventory.size() / 25) + 1) > 1)
		{
			DrawTexture(this->Next, 1525, 545, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), { 1521, 545, (float)this->Next.width, (float)this->Next.height }))
			{
				DrawTexture(this->NextHover, 1525, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page++;
			}
		}
		if (page > 1 && page == int(this->inventory.size() / 25) + 1)
		{
			DrawTexture(this->Prev, 340, 545, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), { 340, 545, (float)this->Prev.width, (float)this->Prev.height }))
			{
				DrawTexture(this->PrevHover, 340, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page--;
			}
		}
		for (size_t i = 0, count = (this->page - 1) * 24; i < 4; i++) {
			for (size_t j = 0; j < 6; j++)
			{
				DrawTexture(this->Slot, 448 + (j * (25 + this->Slot.width)), 245 + (i * (25 + this->Slot.height)), WHITE);
				DrawTextEx(gameManager->ArialBold, (this->inventory[count].name).c_str(), { float(501 + (j * (122 + this->Flask.width)) + (this->Flask.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].name).c_str(), 20, 1).x / 2)), float(319 + (i * (81 + this->Flask.height)) + (this->Flask.height / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].name).c_str(), 20, 1).y / 2)) }, 20, 1, BLACK);
				DrawTextEx(gameManager->ArialBold, (this->inventory[count].symbol).c_str(), { float(443 + (j * (125 + this->Flask.width)) + (this->Flask.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].symbol).c_str(), 20, 1).x / 2)), float(215 + (i * (80 + this->Flask.height)) + (this->Flask.height / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].symbol).c_str(), 20, 1).y / 2)) }, 20, 1, BLACK);
				DrawTextEx(gameManager->ArialBold, std::to_string(this->inventory[count].quantity).c_str(), { float(543 + (j * (124 + this->Flask.width)) + (this->Flask.width / 2) - (MeasureTextEx(gameManager->ArialBold, std::to_string(this->inventory[count].quantity).c_str(), 20, 1).x / 2)), float(215 + (i * (80 + this->Flask.height)) + (this->Flask.height / 2) - (MeasureTextEx(gameManager->ArialBold, std::to_string(this->inventory[count].quantity).c_str(), 20, 1).y / 2)) }, 20, 1, BLACK);
				DrawTexture(this->Flask, 497 + (j * (123 + this->Flask.width)), 260 + (i * (80 + this->Flask.height)), WHITE);
				count++;
				if (count >= inventory.size()) break;
			}
			if (count >= inventory.size()) break;
		}
		if (gameManager->IsButtonClicked("CLOSE"))
		{
			isInventoryOpen = false;
			gameManager->UnloadButton("CLOSE");
		}
		return;
	}
	this->page = 1;
}

void Game::DrawOrder() {
	Orders::Order order = orders->getCurrentOrder();
	//check if the name is empty
	if (order.product == "") return;
	DrawTextEx(gameManager->ArialBold, (order.product + "(" + order.formula + "):").c_str(), {200, 300}, 35, 1, SKYBLUE);
	for (size_t i = 0; i < order.reactants.size(); i++) {
		DrawTextEx(gameManager->ArialBold, (std::to_string(order.reactants[i].quantity) + "x " + order.reactants[i].name).c_str(), {220, float(360 + i * 42)}, 35, 1, WHITE);
	}
	DrawTextEx(gameManager->ArialBold, ("Reward: " + std::to_string(order.price) + "$").c_str(), {510, 545}, 35, 1, GREEN);
}