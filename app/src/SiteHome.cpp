#pragma once
#include <SiteHome.hpp>

SiteHome::SiteHome() {
	gameManager->LoadScene(gameManager->SCENE::SITEHOME, { "Site/SiteHome.png" }, { {0, 0} });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions);
	gameManager->LoadButtons({ "Site/Unlock.png" }, { "Site/UnlockHover.png" }, { {1525, 900} });
	while (gameManager->CurrentScene == gameManager->SCENE::SITEHOME && !gameManager->GetShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		EndDrawing();

		if (gameManager->IsButtonClicked(0) || this->currTab == TABS::ELEMENTS) {
			this->currTab = TABS::ELEMENTS;
			tableManager->Update();
		}
		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this->tableManager;
			delete this;
			Game* menu = new Game();
			break;
		}
		if (gameManager->IsButtonClicked(1)) {
			this->currTab = SiteHome::TABS::ORDERS;
			orders->Update();
		}
	}
}
SiteHome::~SiteHome() {}