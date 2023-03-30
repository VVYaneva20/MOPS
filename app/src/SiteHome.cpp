#pragma once
#include <SiteHome.hpp>

SiteHome::SiteHome() {
	gameManager->LoadScene(gameManager->SCENE::SITEHOME, {}, {});
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
			gameManager->UnloadButtonByID(4);
			tableManager->loaded = false;
			this->currTab = TABS::ORDERS;
			orders->Update();
		}
		gameManager->Update();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this->tableManager;
			delete this;
			Game* menu = new Game();
			break;
		}
	}
}
SiteHome::~SiteHome() {}