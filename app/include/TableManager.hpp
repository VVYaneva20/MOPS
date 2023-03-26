#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include <GameManager.hpp>
#include <json.h>
#include <fstream>

class TableManager {
public:
	TableManager();
	~TableManager();
	void Update();
private:
	GameManager* gameManager = GameManager::GetInstance();
	
	struct PeriodicElement {
		const char* name;
		const char* appearance;
		float atomicMass;
		int boil;
		const char* category;
		float density;
		float melt;
		float molarHeat;
		int atomicNumber;
		int period;
		int group;
		const char* phase;
		const char* summary;
		const char* symbol;
		int posX;
		int posY;
	};
	
	Texture2D tableOutline = LoadTexture((gameManager->GetAssetPath() + "Table/TableOutline.png").c_str());
	Texture2D hydrogen = LoadTexture((gameManager->GetAssetPath() + "Table/Hydrogen.png").c_str());
	void DrawPeriodicTable(std::vector<PeriodicElement> elements);
	std::vector<PeriodicElement> setPeriodicElements(std::vector<PeriodicElement> &elements);
	
	std::vector<PeriodicElement> m_Elements;
};