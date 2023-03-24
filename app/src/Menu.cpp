#include <Menu.hpp>

Menu::Menu() {
    gameManager->LoadScene(gameManager->SCENE::MENU, this->m_Images, { { 0, 0 }, this->m_LogoPos });
    gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions);
    this->DrawMenu();
}

Menu::~Menu() {}

void Menu::DrawMenu() {
    while (gameManager->CurrentScene == gameManager->SCENE::MENU && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        if (IsKeyPressed(KEY_ESCAPE)) {
            delete gameManager;
            break;
        }
        EndDrawing();
    }
}