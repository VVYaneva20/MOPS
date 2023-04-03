#include <Rules.hpp>


Rules::Rules() {

    if (gameManager->currentTheme == gameManager->THEME::THEME_LIGHT) {
        gameManager->LoadScene(gameManager->SCENE::RULES, { "Rules/Rules.png" }, { {0, 0} });
        gameManager->LoadButtons(this->m_ButtonsLight, this->m_ButtonsHoverLight, this->m_ButtonPositions, this->m_ButtonNames);
    }
    if (gameManager->currentTheme == gameManager->THEME::THEME_DARK) {
        gameManager->LoadScene(gameManager->SCENE::RULES, { "Rules/RulesDark.png" }, { { 0, 0 } });
        gameManager->LoadButtons(this->m_ButtonsDark, this->m_ButtonsHoverDark, this->m_ButtonPositions, this->m_ButtonNames);
    }

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
            std::cout << "Exit" << std::endl;
            delete gameManager;
            break;
        }
    }
}

Rules::~Rules() {}

SecondPage::SecondPage() {
    if (gameManager->currentTheme == gameManager->THEME::THEME_LIGHT) {
        gameManager->LoadScene(gameManager->SCENE::SECONDRULES, { "Rules/RulesSecond.png" }, { {0, 0} });
        gameManager->LoadButtons(this->m_ButtonsLight, this->m_ButtonsHoverLight, this->m_ButtonPositions, this->m_ButtonNames);
    }
    if (gameManager->currentTheme == gameManager->THEME::THEME_DARK) {
        gameManager->LoadScene(gameManager->SCENE::SECONDRULES, { "Rules/RulesDarkSecond.png" }, { { 0, 0 } });
        gameManager->LoadButtons(this->m_ButtonsDark, this->m_ButtonsHoverDark, this->m_ButtonPositions, this->m_ButtonNames);
    }

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
            std::cout << "Exit" << std::endl;
            delete gameManager;
            break;
        }
    }
}

SecondPage::~SecondPage() {}
