#include <Rules.hpp>

Rules::Rules() {
    gameManager->LoadScene(gameManager->SCENE::RULES, { "Rules/Rules.png" }, { { 0, 0 } });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames);

    while (gameManager->CurrentScene == gameManager->SCENE::RULES && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        EndDrawing();

        

        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            std::cout << "Exit" << std::endl;
            delete gameManager;
            break;
        }
    }
}

Rules::~Rules() {}