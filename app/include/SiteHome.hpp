#pragma once
#include <GameManager.hpp>
#include <Menu.hpp>
#include <TableManager.hpp>
#include <Orders.hpp>
#include <Upgrades.hpp>

class SiteHome {
public:
	SiteHome();
	~SiteHome();

	enum TABS {
		ELEMENTS, 
		ORDERS,
		UPGRADES
	};
private:
	GameManager* gameManager = GameManager::GetInstance();
	TableManager* tableManager;
	Upgrades* upgrades;
	Orders* orders = Orders::GetInstance();
	SiteHome::TABS currTab;
	void Update();
	std::vector<std::string> m_Buttons = { "Site/Elements.png", "Site/Orders.png", "Site/Upgrades.png", "Site/Close.png"};
	std::vector<std::string> m_ButtonsHover = { "Site/ElementsHover.png", "Site/OrdersHover.png", "Site/UpgradesHover.png", "Site/CloseHover.png"};
	std::vector<Vector2> m_ButtonPositions = { {400, 35}, {680, 35}, {944, 35}, {1801, 0} };
	std::vector<std::string> m_ButtonNames = { "Elements", "Orders", "Upgrades", "Close" };
	std::vector<bool> m_hasTheme = { false, false, false, false };
};