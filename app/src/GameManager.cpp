#pragma once
#include <GameManager.hpp>

GameManager* GameManager::instance;

GameManager::GameManager() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(this->m_ScreenSize.x, this->m_ScreenSize.y, "MOPS CHEMISTRY LAB");
	SetExitKey(KEY_NULL);
	this->Arial = LoadFontEx((this->GetAssetPath() + "Arial.ttf").c_str(), 1000, 0, 0);
	this->ArialBold = LoadFontEx((this->GetAssetPath() + "arialbd.ttf").c_str(), 70, 0, 0);
	SetTextureFilter(this->ArialBold.texture, TEXTURE_FILTER_POINT);
	std::ifstream file(this->GetAssetPath() + "savedata.json");
	Json::Value root;
	file >> root;
	file.close();
	this->m_Balance = root["balance"].asInt();
	//ToggleFullscreen();
};

GameManager::~GameManager() {
	std::ifstream file(this->GetAssetPath() + "savedata.json");
	Json::Value root;
	file >> root;
	root["balance"] = this->m_Balance;
	std::ofstream file2(this->GetAssetPath() + "savedata.json");
	file2 << root;
	file.close();
	file2.close();
	CloseWindow();
};

void GameManager::Update() {
	this->m_MousePos = GetMousePosition();
	DrawTextures();
	DrawButtons();
	DrawMousePos();
};

void GameManager::LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<Vector2> positions) {
	if (this->CurrentScene != sceneID) {
		UnloadScene();
		this->CurrentScene = sceneID;
		for (int i = 0; i < textures.size(); i++) {
			textures[i] = this->GetAssetPath() + textures[i];
			this->m_Textures.push_back(LoadTexture(textures[i].c_str()));
			this->m_TexturePositions.push_back(positions[i]);
			std::cout << "Loaded Texture: " << textures[i] << std::endl;
		}
	}
}

void GameManager::LoadButtons(std::vector<std::string> textureFiles, std::vector<std::string> onHoverTextures, std::vector<Vector2> positions, std::vector<std::string> names)
{
	for (size_t i = 0; i < textureFiles.size(); i++)
	{
		textureFiles[i] = this->GetAssetPath() + textureFiles[i];
		onHoverTextures[i] = this->GetAssetPath() + onHoverTextures[i];
		std::transform(names[i].begin(), names[i].end(), names[i].begin(), ::toupper);
		BUTTON button = { names[i], LoadTexture(textureFiles[i].c_str()), LoadTexture(onHoverTextures[i].c_str()), positions[i]};
		this->m_Buttons.push_back(button);
		
	}
}

void GameManager::DrawMousePos() {
	DrawText(TextFormat("Mouse Position: %g, %g", this->m_MousePos.x, this->m_MousePos.y), 10, 100, 20, BLACK);
}

void GameManager::DrawTextures() {
	for (int i = 0; i < m_Textures.size(); i++) {
		DrawTextureEx(this->m_Textures[i], this->m_TexturePositions[i], 0, GetScreenSize().x / this->m_ScreenSize.x, WHITE);
	}
}

void GameManager::DrawButtons() {
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	for (size_t i = 0; i < this->m_Buttons.size(); i++)
	{
		DrawTexture(this->m_Buttons[i].texture, this->m_Buttons[i].pos.x, this->m_Buttons[i].pos.y, WHITE);
		Rectangle buttonRect = { this->m_Buttons[i].pos.x, this->m_Buttons[i].pos.y, this->m_Buttons[i].texture.width, this->m_Buttons[i].texture.height };
		if (CheckCollisionPointRec(this->m_MousePos, buttonRect))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			DrawTexture(this->m_Buttons[i].onHoverTexture, this->m_Buttons[i].pos.x, this->m_Buttons[i].pos.y, WHITE);
		}
	}
}

void GameManager::UnloadButton(size_t ID)
{
	for (size_t i = 0; i < this->m_Buttons.size(); i++)
	{
		if (i == ID)
		{
			UnloadTexture(this->m_Buttons[i].texture);
			UnloadTexture(this->m_Buttons[i].onHoverTexture);
			this->m_Buttons.erase(this->m_Buttons.begin() + i);
			break;
		}
	}
}

void GameManager::UnloadButton(std::string name)
{
	for (size_t i = 0; i < this->m_Buttons.size(); i++)
	{
		if (this->m_Buttons[i].name == name)
		{
			UnloadTexture(this->m_Buttons[i].texture);
			UnloadTexture(this->m_Buttons[i].onHoverTexture);
			this->m_Buttons.erase(this->m_Buttons.begin() + i);
			break;
		}
	}
}

void GameManager::UnloadScene() {
	for (int i = 0; i < this->m_Textures.size(); i++) {
		UnloadTexture(this->m_Textures[i]);
	}
	this->m_Textures.clear();
	this->m_TexturePositions.clear();

	for (int i = 0; i < this->m_Buttons.size(); i++) {
		UnloadTexture(this->m_Buttons[i].texture);
		UnloadTexture(this->m_Buttons[i].onHoverTexture);
	}
	this->m_Buttons.clear();
}

std::string GameManager::GetAssetPath()
{
	return this->m_AssetPath;
}

Vector2 GameManager::GetScreenSize() {
	return Vector2{ float(GetScreenWidth()), float(GetScreenHeight()) };
}

GameManager* GameManager::GetInstance() {
	if (!instance) instance = new GameManager();
	return instance;
}

bool GameManager::GetShouldClose() {
	return WindowShouldClose();
}

bool GameManager::IsButtonClicked(size_t buttonID)
{
	if (buttonID >= this->m_Buttons.size())
	{
		std::cout << "Button ID out of range\n";
		return false;
	}
	Rectangle buttonRect = { this->m_Buttons[buttonID].pos.x, this->m_Buttons[buttonID].pos.y, this->m_Buttons[buttonID].texture.width, this->m_Buttons[buttonID].texture.height };
	if (CheckCollisionPointRec(this->m_MousePos, buttonRect))
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			return true;
		}
	}
	return false;
}

bool GameManager::IsButtonClicked(std::string buttonName)
{
	std::transform(buttonName.begin(), buttonName.end(), buttonName.begin(), ::toupper);
	for (size_t i = 0; i < this->m_Buttons.size(); i++)
	{
		if (this->m_Buttons[i].name == buttonName)
		{
			Rectangle buttonRect = { this->m_Buttons[i].pos.x, this->m_Buttons[i].pos.y, this->m_Buttons[i].texture.width, this->m_Buttons[i].texture.height };
			if (CheckCollisionPointRec(this->m_MousePos, buttonRect))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					return true;
				}
			}
		}
	}
	return false;
}

int GameManager::GetBalance()
{
	return this->m_Balance;
}

void GameManager::SetBalance(int balance)
{
	this->m_Balance = balance;
}