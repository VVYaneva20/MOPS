#include <GameManager.hpp>
#include <Menu.hpp>

int main() {
	//Gets the game manager instance
	GameManager* gameManager = GameManager::GetInstance();

	//Initializes the menu
	Menu* mainMenu = new Menu();
	return 0;
}