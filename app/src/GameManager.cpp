#pragma once
#include <GameManager.hpp>

GameManager* GameManager::instance;

GameManager::GameManager() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(this->m_ScreenSize.x, this->m_ScreenSize.y, "MOPS GAME");
	SetExitKey(KEY_NULL);
	//ToggleFullscreen();
};

GameManager::~GameManager() {
	CloseWindow();
};

void GameManager::Update() {
	DrawTextures();
	DrawButtons();
};

void GameManager::LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<std::string> hoverEffects, std::vector<Vector2> positions) {
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

void GameManager::LoadButtons(std::vector<std::string> textureFiles, std::vector<std::string> onHoverTextures, std::vector<Vector2> positions)
{
	for (size_t i = 0; i < textureFiles.size(); i++)
	{
		textureFiles[i] = this->GetAssetPath() + textureFiles[i];
		onHoverTextures[i] = this->GetAssetPath() + onHoverTextures[i];
		this->m_Buttons.push_back(LoadTexture(textureFiles[i].c_str()));
		this->m_OnHoverButtons.push_back(LoadTexture(onHoverTextures[i].c_str()));
		this->m_ButtonPositions.push_back(positions[i]);
	}
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
		DrawTexture(this->m_Buttons[i], this->m_ButtonPositions[i].x, this->m_ButtonPositions[i].y, WHITE);
		Rectangle buttonRect = { this->m_ButtonPositions[i].x, this->m_ButtonPositions[i].y, this->m_Buttons[i].width, this->m_Buttons[i].height };
		if (CheckCollisionPointRec(this->m_MousePos, buttonRect))
		{
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			DrawTexture(this->m_OnHoverButtons[i], this->m_ButtonPositions[i].x, this->m_ButtonPositions[i].y, WHITE);
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
		UnloadTexture(this->m_Buttons[i]);
		UnloadTexture(this->m_OnHoverButtons[i]);
	}
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