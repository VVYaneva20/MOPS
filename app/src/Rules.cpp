#include <Rules.hpp>


Rules::Rules() {
	gameManager->LoadScene(gameManager->SCENE::RULES, { "Rules/Rules.png" }, { { 0, 0 } }, { true });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);

    while (gameManager->CurrentScene == gameManager->SCENE::RULES && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        EndDrawing();

        if (gameManager->IsButtonClicked("BACK")) {
            delete this;
            Menu* menu = new Menu();
            break;
        }
        if (gameManager->IsButtonClicked("NEXT"))
        {
            delete this;
            SecondPage* secondPage = new SecondPage();
            break;
        }

        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            delete this;
			Menu* menu = new Menu();
			break;
        }
    }
}

Rules::~Rules() {}

SecondPage::SecondPage() {
    gameManager->LoadScene(gameManager->SCENE::SECONDRULES, { "Rules/RulesSecond.png" }, { {0, 0} }, { true });
	gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);

    while (gameManager->CurrentScene == gameManager->SCENE::SECONDRULES && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        EndDrawing();

        if (gameManager->IsButtonClicked("BACK")) {
            delete this;
            Rules* rules = new Rules();
            break;
        }

        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            delete this;
            Menu* menu = new Menu();
            break;
        }
    }
}

SecondPage::~SecondPage() {}
