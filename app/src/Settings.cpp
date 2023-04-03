#include <Settings.hpp>

Settings::Settings() {
	gameManager->LoadScene(gameManager->currentTheme == gameManager->THEME::THEME_DARK ? gameManager->SCENE::SETTINGS_DARK : gameManager->SCENE::SETTINGS_LIGHT, { "Settings/Settings.png" }, { { 0, 0 } }, { true });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
	this->DrawSettings();
}

void Settings::DrawSettings() {
	while ((gameManager->CurrentScene == gameManager->SCENE::SETTINGS_LIGHT || gameManager->CurrentScene == gameManager->SCENE::SETTINGS_DARK) && !gameManager->GetShouldClose()) {
		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		gameManager->DrawCursor();
		EndDrawing();

		if (gameManager->IsButtonClicked("BACK")) {
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (gameManager->IsButtonClicked("THEME")) {
			if (gameManager->currentTheme == gameManager->THEME_LIGHT) {
				gameManager->currentTheme = gameManager->THEME_DARK;
			}
			else if (gameManager->currentTheme == gameManager->THEME::THEME_DARK) {
				gameManager->currentTheme = gameManager->THEME_LIGHT;
			}
			Settings* settings = new Settings();
			delete Orders::GetInstance();
			delete this;
			break;
		}

		if (gameManager->IsButtonClicked("CURSOR"))
		{
			//gameManager->SetCursor(gameManager->CURSORS::FLASK);
			//set the cursor to the next in the enum
			if (gameManager->currentCursor == gameManager->CURSOR::MOPS || (gameManager->currentCursor + 1 == gameManager->CURSOR::MOPS && !gameManager->CursorUpgrade))
			{
				gameManager->SetCursor(gameManager->CURSOR::DEFAULT);
				continue;
			}
			//std::cout << 11111111111;
			GameManager::CURSOR cursor = GameManager::CURSOR(gameManager->currentCursor + 1);
			std::cout << gameManager->currentCursor << "  ";
			std::cout << cursor << std::endl;
			gameManager->SetCursor(cursor);
			
		}

		if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
			std::cout << "Exit" << std::endl;
			delete gameManager;
			break;
		}
	}
}

Settings::~Settings() {
}