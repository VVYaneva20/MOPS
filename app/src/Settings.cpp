#include <Settings.hpp>

Settings::Settings() {
	//if (gameManager->currentTheme == gameManager->THEME::THEME_LIGHT) {
	//	gameManager->LoadScene(gameManager->SCENE::SETTINGS_LIGHT, { "Settings/Settings.png" }, { { 0, 0 } });
	//	gameManager->LoadButtons(this->m_ButtonsLight, this->m_ButtonsHoverLight, this->m_ButtonPositions, this->m_ButtonNames);
	//}
	//if (gameManager->currentTheme == gameManager->THEME::THEME_DARK) {
	//	gameManager->LoadScene(gameManager->SCENE::SETTINGS_DARK, { "Settings/DarkTheme.png" }, { { 0, 0 } });
	//	gameManager->LoadButtons(this->m_ButtonsDark, this->m_ButtonsHoverDark, this->m_ButtonPositions, this->m_ButtonNames);
	//}
	gameManager->LoadScene(gameManager->currentTheme == gameManager->THEME::THEME_DARK ? gameManager->SCENE::SETTINGS_DARK : gameManager->SCENE::SETTINGS_LIGHT, { "Settings/Settings.png" }, { { 0, 0 } }, {1});
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
	this->DrawSettings();
}

void Settings::DrawSettings() {
	while ((gameManager->CurrentScene == gameManager->SCENE::SETTINGS_LIGHT || gameManager->CurrentScene == gameManager->SCENE::SETTINGS_DARK) && !gameManager->GetShouldClose()) {
		BeginDrawing();
		ClearBackground(BLUE);
		EndDrawing();
		gameManager->Update();

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
			delete this;
			break;
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