#include <Menu.hpp>

Menu::Menu() {
	gameManager->LoadScene(gameManager->SCENE::MENU, { "" }, { "" }, { { 0, 0 } });
	gameManager->LoadButtons({ "" }, { "" }, { { 0, 0 } });
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