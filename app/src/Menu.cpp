#include <Menu.hpp>

Menu::Menu() {
	gameManager->LoadScene(gameManager->SCENE::MENU, this->m_Textures, { {0,0}, this->m_LogoPos }, { true, false });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
    this->DrawMenu();
}
Menu::~Menu() {
}


void Menu::DrawMenu() {
    while (gameManager->CurrentScene == gameManager->SCENE::MENU && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        gameManager->DrawCursor();
        EndDrawing();

        if (gameManager->IsButtonClicked("START")) {
            delete this;
            Game* game = new Game();
            break;
        }
        if (gameManager->IsButtonClicked("SETTINGS")) {
			delete this;
			Settings* settings = new Settings();
			break;
		}
        if (gameManager->IsButtonClicked("RULES")) {
			delete this;
			Rules* rules = new Rules();
			break;
		}

        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            delete orders;
            delete gameManager;
            break;
        }
    }
}