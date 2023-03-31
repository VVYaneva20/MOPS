#pragma once
#include <SiteHome.hpp>

SiteHome::SiteHome() {
	gameManager->LoadScene(gameManager->SCENE::SITEHOME, { "Site/Balance.png" }, { { 0, 27 } });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames);
	
	this->tableManager = new TableManager();
	this->orders = new Orders();
	
	while (gameManager->CurrentScene == gameManager->SCENE::SITEHOME && !gameManager->GetShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);
		if (gameManager->IsButtonClicked("ELEMENTS") || this->currTab == TABS::ELEMENTS) {
			this->currTab = TABS::ELEMENTS;
			tableManager->Update();
		}
		if (gameManager->IsButtonClicked("ORDERS") || this->currTab == TABS::ORDERS) {
			this->currTab = TABS::ORDERS;
			orders->Update();
		}
		gameManager->Update();
		DrawTextEx(gameManager->ArialBold, (std::to_string(gameManager->GetBalance()) + "$").c_str(), { 70, 30 }, 60, 1, WHITE);
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("CLOSE"))
		{
			delete this->tableManager;
			delete this;
			Game* menu = new Game();
			break;
		}
	}
}
SiteHome::~SiteHome() {}