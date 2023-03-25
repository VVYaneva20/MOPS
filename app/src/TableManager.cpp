#include <TableManager.hpp>

TableManager::TableManager() {
	this->Update();
}

TableManager::~TableManager() {}

void TableManager::Update() {
	DrawTextureEx(this->tableOutline, { 30, 300 }, 0, 1, WHITE);
}