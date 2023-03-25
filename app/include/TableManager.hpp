#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include <GameManager.hpp>

class TableManager {
public:
	TableManager();
	~TableManager();
	void Update();
private:
	GameManager* gameManager = GameManager::GetInstance();
	
	struct PeriodicElement {
		std::string name;
		std::string symbol;
		Vector2 position;
	};
	
	Texture2D tableOutline = LoadTexture((gameManager->GetAssetPath() + "Table/TableOutline.png").c_str());
	void DrawPeriodicTable(std::vector<PeriodicElement> elements);

	std::vector<PeriodicElement> m_Elements;
};