#include <Settings.hpp>

Settings::Settings(THEME currentTheme) {
	m_CurrentTheme = currentTheme;
	if (m_CurrentTheme == THEME_LIGHT) {
		gameManager->LoadScene(gameManager->SCENE::SETTINGS_LIGHT, { "Settings/Settings.png" }, { { 0, 0 } });
		gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames);
	}
	if (m_CurrentTheme == THEME_DARK) {
		gameManager->LoadScene(gameManager->SCENE::SETTINGS_DARK, { "Settings/DarkTheme.png" }, { { 0, 0 } });
		gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames);
	}
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
			if (m_CurrentTheme == THEME_LIGHT) {
				m_CurrentTheme = THEME_DARK;
				Settings* settings = new Settings(m_CurrentTheme); 
				delete this;
				break;
			}
			else if (m_CurrentTheme == THEME_DARK) {
				m_CurrentTheme = THEME_LIGHT;
				Settings* settings = new Settings(m_CurrentTheme);
				delete this;
				break;
			}
			gameManager->Update();
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