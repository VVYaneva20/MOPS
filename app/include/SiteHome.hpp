#pragma once
#include <GameManager.hpp>
#include <Menu.hpp>
#include <TableManager.hpp>

class SiteHome {
public:
	SiteHome();
	~SiteHome();
private:
	GameManager* gameManager = GameManager::GetInstance();
	TableManager* tableManager = new TableManager();
};