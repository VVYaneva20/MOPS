#include <Game.hpp>

Game::Game() {
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png" }, { {0, 0} });
	gameManager->LoadButtons({ "Lab/PC.png" }, { "Lab/PCHover.png" }, { { 1580, 575 } }, { "PC" });
	this->Update();
}

void Game::Update()
{
	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		orders->generateOrder();
		
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
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (gameManager->IsButtonClicked("PC"))
		{
			delete this;
			SiteHome* siteHome = new SiteHome();
			break;
		}
	}
}

Game::~Game() {}