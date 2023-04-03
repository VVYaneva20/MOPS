#include <Menu.hpp>

Menu::Menu() {
	//Loads the current scene
	gameManager->LoadScene(gameManager->SCENE::MENU, this->m_Textures, { {0,0}, this->m_LogoPos }, { true, false });
	//Loads all buttons
    gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
    this->DrawMenu();
}
Menu::~Menu() {
}


void Menu::DrawMenu() {
	//Draws the menu
    while (gameManager->CurrentScene == gameManager->SCENE::MENU && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        gameManager->DrawCursor();
        EndDrawing();

		//If the start button is clicked then the game starts
        if (gameManager->IsButtonClicked("START")) {
            delete this;
            Game* game = new Game();
            break;
        }
		//If the settings button is clicked then the settings menu is loaded
        if (gameManager->IsButtonClicked("SETTINGS")) {
			delete this;
			Settings* settings = new Settings();
			break;
		}
		//If the rules button is clicked then the rules menu is loaded
        if (gameManager->IsButtonClicked("RULES")) {
			delete this;
			Rules* rules = new Rules();
			break;
		}

		//If escape or exit button is pressed then the game closes
        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            delete orders;
            delete gameManager;
            break;
        }
    }
}