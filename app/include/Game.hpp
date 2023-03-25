#pragma once
#include <GameManager.hpp>
#include <TableManager.hpp>
#include <Menu.hpp>

class Game {
public:
	Game();
	~Game();
private:
	GameManager* gameManager = GameManager::GetInstance();
};