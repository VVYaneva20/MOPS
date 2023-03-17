#pragma once
#include <GameManager.hpp>

GameManager* GameManager::instance;

GameManager::GameManager() {};

GameManager::~GameManager() {};

GameManager *GameManager::GetInstance() {
	if (!instance) instance = new GameManager();
	return instance;
}