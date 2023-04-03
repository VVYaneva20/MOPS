#pragma once
#include <GameManager.hpp>
#include <json.h>
#include <fstream>

class Upgrades {
public:
	Upgrades();
	~Upgrades();
	void Update();
private:
	struct UPGRADES {
		Texture2D button;
		Texture2D buttonHover;
		bool unlocked;
		int price;
	};
	std::vector<UPGRADES> m_Upgrades;
	GameManager* gameManager = GameManager::GetInstance();
	Texture2D background = LoadTexture((gameManager->GetAssetPath() + "Upgrades/Background.png").c_str());
	Texture2D Unlocked = LoadTexture((gameManager->GetAssetPath() + "Upgrades/Unlocked.png").c_str());
	bool UnlockedIncome;
	bool UnlockedFrequency;
	bool UnlockedCursor;
};