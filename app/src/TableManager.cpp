#include <TableManager.hpp>

TableManager::TableManager() {
	this->m_Elements = setPeriodicElements(this->m_Elements);
	this->Update();
}

TableManager::~TableManager() {}

void TableManager::Update() {
	DrawTextureEx(this->tableOutline, { 30, 300 }, 0, 1, WHITE);
	DrawPeriodicTable(this->m_Elements);
}

void TableManager::DrawPeriodicTable(std::vector<TableManager::PeriodicElement> elements) {
	for (size_t i = 0; i < elements.size(); i++) {
		DrawTexture(this->hydrogen, elements[i].posX, elements[i].posY, WHITE);
	}
}

std::vector<TableManager::PeriodicElement> TableManager::setPeriodicElements(std::vector<PeriodicElement> &elements) {
	Json::Value root;
	std::ifstream("./assets/elements/elements.json") >> root;
	for (int i = 0; i < 118; i++) {
		PeriodicElement element;
		element.name = root["elements"][i]["name"].asCString();
		if (root["elements"][i]["appearance"].isNull()) element.appearance = "UNKNOWN";
		else element.appearance = root["elements"][i]["appearance"].asCString();
		element.atomicMass = root["elements"][i]["atomic_mass"].asFloat();
		element.boil = root["elements"][i]["boil"].asInt();
		element.category = root["elements"][i]["category"].asCString();
		element.density = root["elements"][i]["density"].asFloat();
		element.melt = root["elements"][i]["melt"].asFloat();
		element.molarHeat = root["elements"][i]["molar_heat"].asFloat();
		element.atomicNumber = root["elements"][i]["number"].asInt();
		element.period = root["elements"][i]["period"].asInt();
		element.group = root["elements"][i]["group"].asInt();
		element.phase = root["elements"][i]["phase"].asCString();
		element.summary = root["elements"][i]["summary"].asCString();
		element.symbol = root["elements"][i]["symbol"].asCString();
		element.posX = root["elements"][i]["posx"].asInt();
		element.posY = root["elements"][i]["posy"].asInt();
		elements.push_back(element);
	}
	return elements;
}