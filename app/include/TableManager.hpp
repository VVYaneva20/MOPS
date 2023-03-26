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
		std::string name;
		std::string appearance;
		float atomicMass;
		int boil;
		std::string category;
		float density;
		float melt;
		float molarHeat;
		int atomicNumber;
		int period;
		int group;
		std::string phase;
		std::string summary;
		std::string symbol;
		int posX;
		int posY;
		bool unlocked;
		int price;
		Texture2D texture;
	};
	
	PeriodicElement m_SelectedElement;

	Texture2D tableOutline = LoadTexture((gameManager->GetAssetPath() + "Table/TableOutline.png").c_str());
	Texture2D padlock = LoadTexture((gameManager->GetAssetPath() + "Elements/padlock.png").c_str());
	void DrawPeriodicTable(std::vector<PeriodicElement> elements);
	void DisplayInfo(PeriodicElement element);
	std::vector<PeriodicElement> setPeriodicElements(std::vector<PeriodicElement> &elements);
	
	std::vector<PeriodicElement> m_Elements;
};