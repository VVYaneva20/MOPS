#include <Settings.hpp>

Settings::Settings() {
	// Loads the current scene
	gameManager->LoadScene(gameManager->currentTheme == gameManager->THEME::THEME_DARK ? gameManager->SCENE::SETTINGS_DARK : gameManager->SCENE::SETTINGS_LIGHT, { "Settings/Settings.png" }, { { 0, 0 } }, { true });
	// Loads all buttons
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
	this->DrawSettings();
}

void Settings::DrawSettings() {
	// Draws the settings menu
	while ((gameManager->CurrentScene == gameManager->SCENE::SETTINGS_LIGHT || gameManager->CurrentScene == gameManager->SCENE::SETTINGS_DARK) && !gameManager->GetShouldClose()) {
		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		gameManager->DrawCursor();
		EndDrawing();

		// If the back button is clicked then the menu is loaded
		if (gameManager->IsButtonClicked("BACK")) {
			delete this;
			Menu* menu = new Menu();
			break;
		}

		// If the theme button is clicked then the theme is changed
		if (gameManager->IsButtonClicked("THEME")) {
			if (gameManager->currentTheme == gameManager->THEME_LIGHT) {
				gameManager->currentTheme = gameManager->THEME_DARK;
			}
			else if (gameManager->currentTheme == gameManager->THEME::THEME_DARK) {
				gameManager->currentTheme = gameManager->THEME_LIGHT;
			}
			orders->Reinitialize();
			Settings* settings = new Settings();
			delete this;
			break;
		}

		// If the cursor button is clicked then the cursor is changed
		if (gameManager->IsButtonClicked("CURSOR"))
		{
			//set the cursor to the next in the enum
			if (gameManager->currentCursor == gameManager->CURSOR::MOPS || (gameManager->currentCursor + 1 == gameManager->CURSOR::MOPS && !gameManager->CursorUpgrade))
			{
				gameManager->SetCursor(gameManager->CURSOR::DEFAULT);
				continue;
			}
			GameManager::CURSOR cursor = GameManager::CURSOR(gameManager->currentCursor + 1);
			gameManager->SetCursor(cursor);
			
		}

		// If escape or exit button is pressed then the game closes
		if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
			Menu* menu = new Menu();
			delete this;
			break;
		}
	}
}

Settings::~Settings() {
}