#include <Game.hpp>

Game::Game() {
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png", "Lab/Balance.png" }, { {0, 0}, {0,0} });
	gameManager->LoadButtons({ "Lab/PC.png", "Lab/Inventory.png" }, { "Lab/PCHover.png", "Lab/InventoryHover.png" }, { {1580, 575}, {956, 396} }, { "PC", "INVENTORY" });
	this->Update();
}

Game::~Game() {}

void Game::Update()
{
	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLUE);
		orders->generateOrder();
		gameManager->Update();
		this->DrawInventory();
		this->m_Balance = gameManager->GetBalance();
		DrawTextEx(gameManager->ArialBold, (std::to_string(m_Balance) + "$").c_str(), {70, 5}, 60, 1, WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), { 1500, 300, 60, 60 }) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			selected = true;
		}
		if(!selected) {
			DrawRectangle(1500, 300, 60, 60, RED);
		}

		if (selected)
		{
			DrawRectangle(GetMousePosition().x -30, GetMousePosition().y -30, 60, 60, RED);
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
			delete this;
			SiteHome* siteHome = new SiteHome();
			break;
		}
	}
}

void Game::DrawInventory()
{
	if (isInventoryOpen) {
		DrawTexture(this->HUD, 335, 140, WHITE);
		if (gameManager->IsButtonClicked("CLOSE"))
		{
			isInventoryOpen = false;
			gameManager->UnloadButton("CLOSE");
		}
	}
}