#pragma once
#include <Site.hpp>
#include <SiteHome.hpp>

Site::Site() {
	gameManager->LoadScene(gameManager->SCENE::REGISTER, { "Site/Register.png" }, {{0, 0}});
	gameManager->LoadButtons({ "Site/RegisterButton.png" }, { "Site/RegisterButtonOnHover.png" }, { { 680, 850 } });
	this->DrawSite();
}

Site::~Site() {
}

void Site::DrawSite() {
	while (gameManager->CurrentScene == gameManager->SCENE::REGISTER && !gameManager->GetShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Game* game = new Game();
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