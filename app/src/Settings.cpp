#include <Settings.hpp>

Settings::Settings() {
	gameManager->LoadScene(gameManager->SCENE::SETTINGS, { "Settings/Settings.png" }, { { 0, 0 } });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames);
	this->DrawSettings();
}

Settings::~Settings() {
}


void Settings::DrawSettings() {
	while (gameManager->CurrentScene == gameManager->SCENE::SETTINGS && !gameManager->GetShouldClose()) {
		BeginDrawing();
		ClearBackground(BLUE);
		EndDrawing();
		gameManager->Update();

		if (gameManager->IsButtonClicked("BACK")) {
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
			std::cout << "Exit" << std::endl;
			delete gameManager;
			break;
		}
	}
}