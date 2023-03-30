#include <Game.hpp>

Game::Game() {
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png" }, { {0, 0} });
	gameManager->LoadButtons({ "Lab/PC.png" }, { "Lab/PCHover.png" }, { { 1580, 575 } });
	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		orders->generateOrder();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (gameManager->IsButtonClicked(0))
		{
			delete this;
			SiteHome* siteHome = new SiteHome();
			break;
		}
	}
}

Game::~Game() {}