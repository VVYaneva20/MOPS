#pragma once
#include <SiteHome.hpp>

SiteHome::SiteHome() {
	gameManager->LoadScene(gameManager->SCENE::SITEHOME, { "Site/SiteHome.png" }, { {0, 0} });
	while (gameManager->CurrentScene == gameManager->SCENE::SITEHOME && !gameManager->GetShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		tableManager->Update();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Game* menu = new Game();
			break;
		}
	}
}
SiteHome::~SiteHome() {}