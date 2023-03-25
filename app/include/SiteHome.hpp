#pragma once
#include <GameManager.hpp>
#include <Menu.hpp>

class SiteHome {
public:
	SiteHome();
	~SiteHome();
private:
	GameManager* gameManager = GameManager::GetInstance();
	TableManager* tableManager = new TableManager();
};