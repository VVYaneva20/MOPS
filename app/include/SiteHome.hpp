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

	std::vector<std::string> m_Buttons = { "Site/Elements.png", "Site/Orders.png", "Site/Buy.png" };
	std::vector<std::string> m_ButtonsHover = { "Site/ElementsHover.png", "Site/OrdersHover.png", "Site/BuyHover.png" };
	std::vector<Vector2> m_ButtonPositions = { {400, 35}, {680, 35}, {944, 35} };
};