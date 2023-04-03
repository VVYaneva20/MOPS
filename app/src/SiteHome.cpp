#pragma once
#include <SiteHome.hpp>

SiteHome::SiteHome() {
	//Gets the game manager instance
	gameManager->LoadScene(gameManager->SCENE::SITEHOME, { "Site/Balance.png" }, { { 0, 27 } }, { false });
	//Loads all buttons
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
	
	this->tableManager = new TableManager();
	this->upgrades = new Upgrades();
	
	this->Update();
}

void SiteHome::Update()
{
	//Draws the site home
	while (gameManager->CurrentScene == gameManager->SCENE::SITEHOME && !gameManager->GetShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLUE);
		//If the elements tab is clicked then the periodic table is loaded
		if (gameManager->IsButtonClicked("ELEMENTS") || this->currTab == TABS::ELEMENTS) {
			this->currTab = TABS::ELEMENTS;
			tableManager->Update();
		}
		//If the orders tab is clicked then the orders menu is loaded
		if (gameManager->IsButtonClicked("ORDERS") || this->currTab == TABS::ORDERS) {
			this->currTab = TABS::ORDERS;
			orders->Update();
		}
		//If the upgrades tab is clicked then the upgrades menu is loaded
		if (gameManager->IsButtonClicked("UPGRADES") || this->currTab == TABS::UPGRADES) {
			this->currTab = TABS::UPGRADES;
			upgrades->Update();
		}
		gameManager->Update();
		DrawTextEx(gameManager->ArialBold, (std::to_string(gameManager->GetBalance()) + "$").c_str(), { 70, 30 }, 60, 1, WHITE);
		gameManager->DrawCursor();
		EndDrawing();

		// If escape or exit button is pressed then the menu is loaded
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