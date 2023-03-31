#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>
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
		int unlockPrice;
		int unitPrice;
		Texture2D texture;
		Model model;
	};
	
	bool drawModel = true;
	Texture2D background = LoadTexture((gameManager->GetAssetPath() + "Table/TableBackground.png").c_str());
	Texture2D tableOutline = LoadTexture((gameManager->GetAssetPath() + "Table/TableOutline.png").c_str());
	Texture2D padlock = LoadTexture((gameManager->GetAssetPath() + "Elements/Padlock.png").c_str());
	Texture2D UnlockButton = LoadTexture((gameManager->GetAssetPath() + "Table/Unlock.png").c_str());
	Texture2D UnlockButtonHover = LoadTexture((gameManager->GetAssetPath() + "Table/UnlockHover.png").c_str());
	Texture2D UnlockButtonLocked = LoadTexture((gameManager->GetAssetPath() + "Table/UnlockLocked.png").c_str());
	Texture2D OrderButton = LoadTexture((gameManager->GetAssetPath() + "Table/Order.png").c_str());
	Texture2D OrderButtonHover = LoadTexture((gameManager->GetAssetPath() + "Table/OrderHover.png").c_str());
	Texture2D OrderButtonLocked = LoadTexture((gameManager->GetAssetPath() + "Table/OrderLocked.png").c_str());
	void DrawPeriodicTable(std::vector<PeriodicElement> elements);
	void DisplayInfo(PeriodicElement element);
	std::vector<PeriodicElement> setPeriodicElements(std::vector<PeriodicElement> &elements);
	
	std::vector<PeriodicElement> m_Elements;
	PeriodicElement m_SelectedElement;
	Camera camera = { 0 };
	void SetCameraSettings(Camera& camera);
	float yaw = 0.0f;
	void Draw3DModel();
	void DrawButtons();
	void UnlockElement();
};