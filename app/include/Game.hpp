#pragma once
#include <GameManager.hpp>
#include <SiteHome.hpp>
#include <Menu.hpp>
#include <raymath.h>
#include <Orders.hpp>
#include <iostream>

class Game {
public:
	Game();
	~Game();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Orders* orders = new Orders();
};