#include <Menu.hpp>

Menu::Menu() {
    //if (gameManager->currentTheme == gameManager->THEME::THEME_LIGHT) {
    //    gameManager->LoadScene(gameManager->SCENE::MENU_LIGHT, this->m_ImagesLight, { { 0, 0 }, this->m_LogoPos });
    //    gameManager->LoadButtons(this->m_ButtonsLight, this->m_ButtonsHoverLight, this->m_ButtonPositions, this->m_ButtonNames);
    //}
    //if (gameManager->currentTheme == gameManager->THEME::THEME_DARK) {
    //    gameManager->LoadScene(gameManager->SCENE::MENU_DARK, this->m_ImagesDark, { { 0, 0 }, this->m_LogoPos});
    //    gameManager->LoadButtons(this->m_ButtonsDark, this->m_ButtonsHoverDark, this->m_ButtonPositions, this->m_ButtonNames);
    //}
	gameManager->LoadScene(gameManager->SCENE::MENU, this->m_Textures, { {0,0}, this->m_LogoPos }, { 1, 0 });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);
    this->DrawMenu();
}

//gameManager->LoadScene(gameManager->SCENE::MENU, this->m_Images, { { 0, 0 }, this->m_LogoPos });
//gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames);

Menu::~Menu() {
}


void Menu::DrawMenu() {
    while (gameManager->CurrentScene == gameManager->SCENE::MENU && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
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
            std::cout << "Exit" << std::endl;
            delete gameManager;
            break;
        }

    }
}