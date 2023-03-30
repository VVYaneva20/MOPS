#pragma once
#include <GameManager.hpp>
#include <Menu.hpp>
#include <TableManager.hpp>
#include <Orders.hpp>

class SiteHome {
public:
	SiteHome();
	~SiteHome();

	enum TABS {
		ELEMENTS, 
		ORDERS,
	};
private:
	GameManager* gameManager = GameManager::GetInstance();
	TableManager* tableManager;
	Orders* orders;
	SiteHome::TABS currTab;
	std::vector<std::string> m_Buttons = { "Site/Elements.png", "Site/Orders.png", "Site/Buy.png", "Site/Close.png"};
	std::vector<std::string> m_ButtonsHover = { "Site/ElementsHover.png", "Site/OrdersHover.png", "Site/BuyHover.png", "Site/CloseHover.png"};
	std::vector<Vector2> m_ButtonPositions = { {400, 35}, {680, 35}, {944, 35}, {1801, 0} };
	std::vector<std::string> m_ButtonNames = { "Elements", "Orders", "Buy", "Close" };
};