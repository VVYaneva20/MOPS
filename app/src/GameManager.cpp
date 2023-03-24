#pragma once
#include <GameManager.hpp>

GameManager* GameManager::instance;

GameManager::GameManager() {};

GameManager::~GameManager() {};

void GameManager::Update() {}

void GameManager::LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<std::string> hoverEffects, std::vector<Vector2> positions) {}

void GameManager::DrawTextures() {}

void GameManager::DrawButtons() {}

void GameManager::UnloadScene() {}

GameManager *GameManager::GetInstance() {
	if (!instance) instance = new GameManager();
	return instance;
}