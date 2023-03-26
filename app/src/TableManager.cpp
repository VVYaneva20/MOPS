#include <TableManager.hpp>

TableManager::TableManager() {
	this->m_Elements = setPeriodicElements(this->m_Elements);
	this->m_SelectedElement = m_Elements[0];
}

TableManager::~TableManager() {}

void TableManager::Update() {
	DrawTextureEx(this->tableOutline, { 30, 300 }, 0, 1, WHITE);
	DrawPeriodicTable(this->m_Elements);
	DisplayInfo(this->m_SelectedElement);
}

void TableManager::DrawPeriodicTable(std::vector<TableManager::PeriodicElement> elements) {
	for (size_t i = 0; i < elements.size(); i++) {
		DrawTextureEx(elements[i].texture, { float(elements[i].posX), float(elements[i].posY) }, 0, 0.1625, WHITE);
		if (!elements[i].unlocked)
		{
			DrawTexture(this->padlock, elements[i].posX + 14, elements[i].posY + 15, WHITE);
			DrawRectangle(elements[i].posX, elements[i].posY, 63, 65, Fade(BLACK, 0.7f));
		}
		if (CheckCollisionPointRec(GetMousePosition(), { (float)elements[i].posX, (float)elements[i].posY, 65, 65 })) {
			// draw a border around the element
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			DrawRectangleLinesEx({ (float)elements[i].posX, (float)elements[i].posY, 65, 65 }, 4, ORANGE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				std::cout << elements[i].name;
				this->m_SelectedElement = elements[i];
			}
		}
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

void TableManager::DisplayInfo(TableManager::PeriodicElement element) {
	DrawTextureEx(element.texture, { 1500, 150 }, 0, 0.35, WHITE);
	DrawTextEx(gameManager->ArialBold, (element.name).c_str(), { 1650, 200 }, 35, 0.4, WHITE);
	DrawTextEx(gameManager->ArialBold, ("Group: " + std::to_string(element.group)).c_str(), { 1500, 320 }, 30, 0.2, WHITE);
	DrawTextEx(gameManager->ArialBold, ("Period: " + std::to_string(element.period)).c_str(), { 1500, 360 }, 30, 0.2, WHITE);
	DrawTextEx(gameManager->ArialBold, ("Category: " + element.category).c_str(), { 1500, 400 }, 30, 0.2, WHITE);
	DrawTextEx(gameManager->ArialBold, ("Phase: " + element.phase).c_str(), { 1500, 440 }, 30, 0.2, WHITE);
	DrawTextEx(gameManager->ArialBold, ("Appearance: " + element.appearance).c_str(), { 1500, 480 }, 30, 0.2, WHITE);
	DrawTextEx(gameManager->ArialBold, ("Atomic mass: " + std::to_string(element.atomicMass)).c_str(), { 1500, 520 }, 30, 0.2, WHITE);
	std::string summary = element.summary;
	for (size_t i = 0, j = 0; i < summary.length(); i++, j++) {
		if (i > 300) {
			summary.insert(i, "...");
			break;
		}
		if (j > 33) {
			if (summary[i] == ' ') {
				summary.insert(i + 1, "\n");
				j = 0;
			}
			if (summary[i] == ',' || summary[i] == '.' || summary[i] == ';' || summary[i] == ':') {
				summary.erase(i + 1, 1);
				summary.insert(i + 1, "\n");
				j = 0;
			}
		}
	}
	DrawTextEx(gameManager->ArialBold, summary.substr(0, 304).c_str(), { 1500, 580 }, 22, 0.2, WHITE);
}

std::vector<TableManager::PeriodicElement> TableManager::setPeriodicElements(std::vector<PeriodicElement> &elements) {
	Json::Value root;
	std::ifstream((gameManager->GetAssetPath() + "elements/elements.json").c_str()) >> root;
	for (int i = 0; i < root["elements"].size(); i++) {
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
		element.texture = LoadTexture((gameManager->GetAssetPath() + "Elements/" + element.name + ".png").c_str());
		element.unlocked = root["elements"][i]["unlocked"].asBool();
		element.price = root["elements"][i]["price"].asInt();
		elements.push_back(element);
	}
	return elements;
}