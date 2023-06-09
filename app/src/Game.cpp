#include <Game.hpp>

Game::Game() {
	//Loads the current scene
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png", "Lab/Balance.png", "Lab/Table.png" }, { { 0, 0 }, { 0, 0 }, { 130, 863 } }, {false, false, false});
	//Loads all buttons from this scene
	gameManager->LoadButtons({ "Lab/PC.png", "Lab/Inventory.png", "Lab/Bowl.png", "Lab/Box.png" }, { "Lab/PCHover.png", "Lab/InventoryHover.png", "Lab/BowlHover.png", "Lab/BoxHover.png" }, { {1580, 575}, {954, 420}, {660,632}, {1594, 921} }, { "PC", "INVENTORY", "BOWL", "BOX"}, {false, false, false, false});
	this->SetInventory();
	this->Update();
}

Game::~Game() {
	//Unloads all textures
	UnloadTexture(this->HUD);
	UnloadTexture(this->Slot);
	UnloadTexture(this->SlotHover);
	UnloadTexture(this->Prev);
	UnloadTexture(this->PrevHover);
	UnloadTexture(this->Next);
	UnloadTexture(this->NextHover);
	UnloadTexture(this->Flask);
	UnloadTexture(this->BigFlask);
	UnloadTexture(this->BigFlaskHover);
	UnloadTexture(this->Bowl);
	
	//Puts all elements from the table to the inventory
	for (size_t i = 0; i < this->tableElements.size(); i++) {
		this->inventory.push_back(this->tableElements[i]);
	}
	
	// Puts all elements from the bowl to the inventory
	for (size_t i = 0; i < this->BowlElements.size(); i++) {
		bool found = false;
		for (size_t j = 0; j < this->inventory.size(); j++)
		{
			if (this->inventory[j].symbol == this->BowlElements[i].symbol) {
				this->inventory[j].quantity += this->BowlElements[i].quantity;
				found = true;
				break;
			}
		}
		if(!found) this->inventory.push_back(this->BowlElements[i]);
	}
	
	//Opens the JSON file
	std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
	Json::Value root;
	file >> root;
	file.close();
	
	//Sets the given properties in the JSON
	for (int i = 0; i < root["inventory"].size(); i++) {
		for (size_t j = 0; j < this->inventory.size(); j++) 
		{
			if (root["inventory"][i]["name"].asCString() == this->inventory[j].name) {
				root["inventory"][i]["quantity"] = this->inventory[j].quantity;
				break;
			}
		}
	}

	// Writes in the JSON
	std::ofstream file2(gameManager->GetAssetPath() + "savedata.json");
	file2 << root;
	file2.close();
}

void Game::Update()
{
	//Updates the current scene
	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);
		orders->GenerateOrder();
		gameManager->Update();
		this->DrawTable();
		this->DrawOrder();
		this->DrawInventory();
		this->ProcessOrder();
		this->m_Balance = gameManager->GetBalance();
		DrawTextEx(gameManager->ArialBold, (std::to_string(m_Balance) + "$").c_str(), { 70, 5 }, 60, 1, WHITE);
		//Opens the inventory
		if ((gameManager->IsButtonClicked("INVENTORY") || IsKeyPressed(KEY_I)) && !isInventoryOpen)
		{
			isInventoryOpen = true;
			gameManager->LoadButtons({ "Lab/Close.png" }, { "Lab/CloseHover.png" }, { { 1516, 140 } }, { "CLOSE" }, {false});
			continue;
		}
		gameManager->DrawCursor();
		EndDrawing();

		//When Escape is pressed the game is closed
		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Menu* menu = new Menu();
			break;
		}

		//Opens the PC
		if (gameManager->IsButtonClicked("PC") && !isInventoryOpen)
		{
			delete this;
			SiteHome* siteHome = new SiteHome();
			break;
		}
	}
}

void Game::SetInventory() {
	//Opens the JSON file
	Json::Value root;
	std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
	file >> root;

	//Reads the inventory items from the JSON and puts them in the vector
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
		//Checks if the curr page is not first or last
		if (page > 1 && page < int(this->inventory.size() / 25) + 1)
		{
			DrawTexture(this->Prev, 340, 545, WHITE);
			
			//Checks if the arrow is hovered
			if (CheckCollisionPointRec(GetMousePosition(), { 340, 545, (float)this->Prev.width, (float)this->Prev.height }))
			{
				DrawTexture(this->PrevHover, 340, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page--;
			}
			DrawTexture(this->Next, 1525, 545, WHITE);
			//Checks if next is hovered
			if (CheckCollisionPointRec(GetMousePosition(), { 1521, 545, (float)this->Next.width, (float)this->Next.height }))
			{
				DrawTexture(this->NextHover, 1525, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page++;
			}
		}
		//Checks if you are on the first page and checks if there is more than one page
		if (page == 1 && (int(this->inventory.size() / 25) + 1) > 1)
		{
			DrawTexture(this->Next, 1525, 545, WHITE);
			//Checks if next is hovered
			if (CheckCollisionPointRec(GetMousePosition(), { 1521, 545, (float)this->Next.width, (float)this->Next.height }))
			{
				DrawTexture(this->NextHover, 1525, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page++;
			}
		}
		//Checks if you are on the last page
		if (page > 1 && page == int(this->inventory.size() / 25) + 1)
		{
			DrawTexture(this->Prev, 340, 545, WHITE);
			//Checks if previous button is hovered
			if (CheckCollisionPointRec(GetMousePosition(), { 340, 545, (float)this->Prev.width, (float)this->Prev.height }))
			{
				DrawTexture(this->PrevHover, 340, 545, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page--;
			}
		}
		//Draws the current page of the inventory
		for (size_t i = 0, count = (this->page - 1) * 24; i < 4; i++) {
			for (size_t j = 0; j < 6; j++)
			{
				if (count >= inventory.size()) break;
				DrawTexture(this->Slot, 448 + (j * (25 + this->Slot.width)), 245 + (i * (25 + this->Slot.height)), WHITE);
				if (CheckCollisionPointRec(GetMousePosition(), { (float)448 + (j * (25 + this->Slot.width)), (float)245 + (i * (25 + this->Slot.height)), (float)this->Slot.width, (float)this->Slot.height }) && inventory[count].quantity > 0)
				{
					DrawTexture(this->SlotHover, 448 + (j * (25 + this->Slot.width)), 245 + (i * (25 + this->Slot.height)), WHITE);
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						if (this->tableElements.size() < 4)
						{
							tableElements.push_back(inventory[count]);
							inventory.erase(inventory.begin() + count);
							if (count >= inventory.size()) break;
						}
					}
				}
				DrawTextEx(gameManager->ArialBold, (this->inventory[count].name).c_str(), { float(501 + (j * (122 + this->Flask.width)) + (this->Flask.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].name).c_str(), 20, 1).x / 2)), float(319 + (i * (81 + this->Flask.height)) + (this->Flask.height / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].name).c_str(), 20, 1).y / 2)) }, 20, 1, BLACK);
				DrawTextEx(gameManager->ArialBold, (this->inventory[count].symbol).c_str(), { float(443 + (j * (125 + this->Flask.width)) + (this->Flask.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].symbol).c_str(), 20, 1).x / 2)), float(215 + (i * (80 + this->Flask.height)) + (this->Flask.height / 2) - (MeasureTextEx(gameManager->ArialBold, (this->inventory[count].symbol).c_str(), 20, 1).y / 2)) }, 20, 1, BLACK);
				DrawTextEx(gameManager->ArialBold, std::to_string(this->inventory[count].quantity).c_str(), { float(543 + (j * (124 + this->Flask.width)) + (this->Flask.width / 2) - (MeasureTextEx(gameManager->ArialBold, std::to_string(this->inventory[count].quantity).c_str(), 20, 1).x / 2)), float(215 + (i * (80 + this->Flask.height)) + (this->Flask.height / 2) - (MeasureTextEx(gameManager->ArialBold, std::to_string(this->inventory[count].quantity).c_str(), 20, 1).y / 2)) }, 20, 1, BLACK);
				DrawTexture(this->Flask, 497 + (j * (123 + this->Flask.width)), 260 + (i * (80 + this->Flask.height)), WHITE);
				if (inventory[count].quantity <= 0)	DrawRectangle((float)452 + (j * (25 + this->Slot.width)), (float)245 + (i * (25 + this->Slot.height)), (float)this->Slot.width - 8, (float)this->Slot.height - 8, Fade(BLACK, 0.5f));
				count++;
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
	//Checks if there is an order and draws it
	if (orders->GetCurrentOrder().buyer != this->order.buyer && orders->GetCurrentOrder().product != this->order.product) {
		this->order = orders->GetCurrentOrder();
		for (size_t i = 0; i < this->order.reactants.size(); i++) {
			InventorySlot el;
			el.name = "";
			el.symbol = order.reactants[i].name;
			el.quantity = 0;
			BowlElements.push_back(el);
		}
	}
	if (order.product == "") return;
	DrawTextEx(gameManager->ArialBold, (order.product + "(" + order.formula + "):").c_str(), { 200, 300 }, 35, 1, SKYBLUE);
	for (size_t i = 0; i < order.reactants.size(); i++) {
		DrawTextEx(gameManager->ArialBold, (std::to_string(order.reactants[i].quantity) + "x " + order.reactants[i].name).c_str(), { 220, float(360 + i * 42) }, 35, 1, WHITE);
	}
	DrawTextEx(gameManager->ArialBold, ("Reward: " + std::to_string(order.price) + "$").c_str(), { 510, 545 }, 35, 1, GREEN);
}

void Game::DrawTable()
{
	//Draws the elements on the table
	for (size_t i = 0; i < this->tableElements.size(); i++)
	{
		if (!tableElements[i].holding) {
			DrawTexture(this->BigFlask, 180 + (i * (20 + this->BigFlask.width)), 665, WHITE);
			DrawTextEx(gameManager->ArialBold, (this->tableElements[i].symbol).c_str(), { float(180 + (i * (20 + this->BigFlask.width)) + (this->BigFlask.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->tableElements[i].symbol).c_str(), 20, 1).x / 2)), 810 }, 20, 1, BLACK);
		}
		if (CheckCollisionPointRec(GetMousePosition(), { float(180 + (i * (20 + this->BigFlask.width))), float(665), (float)this->BigFlask.width, (float)this->BigFlask.height }) && !this->holding)
		{
			DrawTexture(this->BigFlaskHover, 180 + (i * (20 + this->BigFlask.width)), 665, WHITE);
			DrawTextEx(gameManager->ArialBold, (this->tableElements[i].symbol).c_str(), { float(180 + (i * (20 + this->BigFlask.width)) + (this->BigFlask.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->tableElements[i].symbol).c_str(), 20, 1).x / 2)), 810 }, 20, 1, Fade(BLACK, 0.5f));
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				tableElements[i].holding = true;
				this->holding = true;
			}
		}
		//Checks if the element is being holded and draws it next to the mouse
		if (tableElements[i].holding)
		{
			DrawTexture(this->BigFlaskHover, GetMousePosition().x - (this->BigFlaskHover.width / 2), GetMousePosition().y - (this->BigFlaskHover.height / 2), WHITE);
			DrawTextEx(gameManager->ArialBold, (this->tableElements[i].symbol).c_str(), { float(GetMousePosition().x - (this->BigFlaskHover.width / 2) + (this->BigFlaskHover.width / 2) - (MeasureTextEx(gameManager->ArialBold, (this->tableElements[i].symbol).c_str(), 20, 1).x / 2)), float(GetMousePosition().y + 46) }, 20, 1, Fade(BLACK, 0.5f));
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				tableElements[i].holding = false;
				this->holding = false;
				if (CheckCollisionPointRec(GetMousePosition(), { 954, 420, 1408, 863 }))
				{
					this->inventory.push_back(tableElements[i]);
					this->tableElements.erase(this->tableElements.begin() + i);
					break;
				}
				if (CheckCollisionPointRec(GetMousePosition(), { 660, 632, 915, 845 })) {
					this->MixReactions(tableElements[i]);
					break;
				}
			}
		}
		if (this->tableElements[i].quantity <= 0)
		{
			this->inventory.push_back(tableElements[i]);
			this->tableElements.erase(this->tableElements.begin() + i);
		}
	}
}

void Game::MixReactions(InventorySlot &el) {
	//Places elements in the bowl
	for (size_t i = 0; i < this->BowlElements.size(); i++) {
		if (this->BowlElements[i].symbol == el.symbol && order.reactants[i].quantity > 0) {
			BowlElements[i].quantity++;
			order.reactants[i].quantity--;
			el.quantity--;
		}
	}
}

void Game::ProcessOrder()
{
	//Checks if the order is ready
	if (!IsReactionReady() || this->order.product.empty() || this->holding) return;
	
	if (IsReactionReady()) {
		DrawTextEx(gameManager->ArialBold, "Place the bowl in the box", { 340, 500 }, 35, 1, SKYBLUE);
	}
	if (gameManager->IsButtonClicked("BOWL"))
	{
		this->holdingBowl = true;
		gameManager->UnloadButton("BOWL");
	}
	if (this->holdingBowl)
	{
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionPointRec(GetMousePosition(), { 1594, 921, 1920, 1080 }))
			{
				gameManager->SetBalance(gameManager->GetBalance() + this->order.price);
				orders->FinishOrder();
				this->BowlElements.clear();
				this->order = {};
			}
			gameManager->LoadButtons({ "Lab/Bowl.png" }, { "Lab/BowlHover.png" }, { { 660, 632 } }, { "BOWL" }, {false});
			this->holdingBowl = false;
		}
		DrawTexture(this->Bowl, GetMousePosition().x - 132, GetMousePosition().y - 117, WHITE);
	}
}

bool Game::IsReactionReady()
{
	//Checks if the quantity of the reactants is right
	for (size_t i = 0; i < this->order.reactants.size(); i++)
	{
		if (order.reactants[i].quantity != 0) return false;
	}
	return true;
}