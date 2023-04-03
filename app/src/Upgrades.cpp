#include <Upgrades.hpp>

Upgrades::Upgrades() {
	Json::Value root;
	std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
	file >> root;
	for (size_t i = 0; i < 3; i++)
	{
		UPGRADES upgrade;
		upgrade.button = LoadTexture((gameManager->GetAssetPath() + "Upgrades/Unlock" + std::to_string(i + 1) + ".png").c_str());
		upgrade.buttonHover = LoadTexture((gameManager->GetAssetPath() + "Upgrades/Unlock" + std::to_string(i + 1) + "Hover.png").c_str());
		m_Upgrades.push_back(upgrade);
	}
	this->m_Upgrades[0].unlocked = root["income"].asBool();
	this->m_Upgrades[1].unlocked = root["frequency"].asBool();
	this->m_Upgrades[2].unlocked = root["cursor"].asBool();
	this->m_Upgrades[0].price = 1500;
	this->m_Upgrades[1].price = 600;
	this->m_Upgrades[2].price = 200;
}

Upgrades::~Upgrades() {
	UnloadTexture(this->background);
	UnloadTexture(this->Unlocked);
	for (size_t i = 0; i < 3; i++)
	{
		UnloadTexture(this->m_Upgrades[i].button);
		UnloadTexture(this->m_Upgrades[i].buttonHover);
	}
}

void Upgrades::Update()
{
	DrawTexture(this->background, 0, 0, WHITE);
	for (int i = 0; i < 3; i++)
	{
		if (this->m_Upgrades[i].unlocked) {
			DrawTexture(this->Unlocked, 104 + (i * (this->Unlocked.width + 106)), 889, WHITE);
			continue;
		}
		DrawTexture(this->m_Upgrades[i].button, 104 + (i * (this->m_Upgrades[i].button.width + 106)), 889, WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), { (float)104 + (i * (this->m_Upgrades[i].button.width + 106)), 889, (float)this->m_Upgrades[i].button.width, (float)this->m_Upgrades[i].button.height })) {
			DrawTexture(this->m_Upgrades[i].buttonHover, 104 + (i * (this->m_Upgrades[i].button.width + 106)), 889, WHITE);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gameManager->GetBalance() >= this->m_Upgrades[i].price) {
				gameManager->SetBalance(gameManager->GetBalance() - this->m_Upgrades[i].price);
				this->m_Upgrades[i].unlocked = true;
				Json::Value root;
				std::ifstream file(gameManager->GetAssetPath() + "savedata.json");
				file >> root;
				switch (i)
				{
				case 0:
					root["income"] = true;
					gameManager->IncomeUpgrade = true;
					break;
				case 1:
					root["frequency"] = true;
					gameManager->OrderFrequencyUpgrade = true;
					break;
				case 2:
					root["cursor"] = true;
					gameManager->CursorUpgrade = true;
					break;
				default:
					break;
				}
				std::ofstream file2(gameManager->GetAssetPath() + "savedata.json");
				file2 << root;
				file2.close();
			}
		}
		
	}
}