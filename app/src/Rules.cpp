#include <Rules.hpp>


Rules::Rules() {
	// Loads the current scene
	gameManager->LoadScene(gameManager->SCENE::RULES, { "Rules/Rules.png" }, { { 0, 0 } }, { true });
	// Loads all buttons
    gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);

	// Draws the rules menu
    while (gameManager->CurrentScene == gameManager->SCENE::RULES && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        EndDrawing();

		// If the back button is pressed then the menu is loaded
        if (gameManager->IsButtonClicked("BACK")) {
            delete this;
            Menu* menu = new Menu();
            break;
        }
		//If the next button is pressed then the next page is loaded
        if (gameManager->IsButtonClicked("NEXT"))
        {
            delete this;
            SecondPage* secondPage = new SecondPage();
            break;
        }
		//If escape or exit button is pressed then the menu loads
        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            delete this;
			Menu* menu = new Menu();
			break;
        }
    }
}

Rules::~Rules() {}

SecondPage::SecondPage() {
	// Loads the current scene
    gameManager->LoadScene(gameManager->SCENE::SECONDRULES, { "Rules/RulesSecond.png" }, { {0, 0} }, { true });
	// Loads all buttons
    gameManager->LoadButtons(this->m_Buttons, this->m_ButtonsHover, this->m_ButtonPositions, this->m_ButtonNames, this->m_hasTheme);

	// Draws the second page of the rules menu
    while (gameManager->CurrentScene == gameManager->SCENE::SECONDRULES && !gameManager->GetShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        gameManager->Update();
        EndDrawing();

		// If the back button is pressed then the first page of the rules menu is loaded
        if (gameManager->IsButtonClicked("BACK")) {
            delete this;
            Rules* rules = new Rules();
            break;
        }

		// If escape or exit button is pressed then the menu loads
        if (IsKeyPressed(KEY_ESCAPE) || gameManager->IsButtonClicked("EXIT")) {
            delete this;
            Menu* menu = new Menu();
            break;
        }
    }
}

SecondPage::~SecondPage() {}
