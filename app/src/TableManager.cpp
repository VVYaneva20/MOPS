#include <TableManager.hpp>

TableManager::TableManager() {
	this->m_Elements = setPeriodicElements(this->m_Elements);
	this->m_Elements[0].model = LoadModel((gameManager->GetAssetPath() + "Models/Hydrogen.glb").c_str());
	this->m_SelectedElement = m_Elements[0];
	this->SetCameraSettings(this->camera);
}

TableManager::~TableManager() {
	for (int i = 0; i < this->m_Elements.size(); i++) {
		UnloadTexture(this->m_Elements[i].texture);
	}
	UnloadModel(this->m_SelectedElement.model);
	UnloadTexture(this->m_SelectedElement.texture);
	UnloadTexture(this->background);
	UnloadTexture(this->tableOutline);
	UnloadTexture(this->padlock);
	UnloadTexture(this->UnlockButton);
	UnloadTexture(this->UnlockButtonHover);
	UnloadTexture(this->UnlockButtonLocked);
	UnloadTexture(this->OrderButton);
	UnloadTexture(this->OrderButtonHover);
	UnloadTexture(this->OrderButtonLocked);
}

void TableManager::Update() {
	DrawTexture(this->background, 0, 0, WHITE);
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
				UnloadModel(this->m_SelectedElement.model);
				elements[i].model = LoadModel((gameManager->GetAssetPath() + "Models/" + elements[i].name + ".glb").c_str());
				this->m_SelectedElement = elements[i];
			}
		}
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

void TableManager::DisplayInfo(TableManager::PeriodicElement element) {
	if (!this->drawModel) DrawTextureEx(element.texture, { 1500, 150 }, 0, 0.35, WHITE);
	else {
		this->Draw3DModel();
		DrawRectangleLinesEx({ 1500, 150, 140, 140 }, 1, BLACK);

	}
	if (CheckCollisionPointRec(GetMousePosition(), { 1500, 150, 140, 140 })) {
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		DrawRectangleLinesEx({ 1500, 150, 140, 140 }, 2, ORANGE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			this->drawModel = !this->drawModel;
		}
	}

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
	this->DrawButtons();
}

std::vector<TableManager::PeriodicElement> TableManager::setPeriodicElements(std::vector<PeriodicElement>& elements) {
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
		element.unlockPrice = root["elements"][i]["unlock_price"].asInt();
		element.unitPrice = root["elements"][i]["unit_price"].asInt();
		if (element.unlocked)
		{
			bool found = false;
			Json::Value inventory;
			std::ifstream((gameManager->GetAssetPath() + "savedata.json").c_str()) >> inventory;
			for (int j = 0; j < inventory["inventory"].size(); j++) {
				if (inventory["inventory"][j]["name"].asCString() == element.symbol) {
					found = true;
					break;
				}
			}
			if (!found) {
				Json::Value newElement;
				newElement["name"] = (element.symbol).c_str();
				newElement["quantity"] = 0;
				inventory["inventory"].append(newElement);
				std::ofstream((gameManager->GetAssetPath() + "savedata.json").c_str()) << inventory;
			}
		}
		elements.push_back(element);
	}
	return elements;
}

void TableManager::SetCameraSettings(Camera& camera) {
	this->camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
	this->camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	this->camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	this->camera.fovy = 10.0f;
	this->camera.projection = CAMERA_PERSPECTIVE;
	SetCameraMode(this->camera, CAMERA_FREE);
}

void TableManager::Draw3DModel()
{
	Model model = this->m_SelectedElement.model;
	UpdateCamera(&this->camera);
	m_SelectedElement.model.transform = MatrixRotateXYZ(Vector3{ DEG2RAD * 1, DEG2RAD * yaw, DEG2RAD * 1 });
	this->camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
	this->yaw += 0.2f;

	BeginMode3D(this->camera);
	DrawModel(m_SelectedElement.model, { 1.326f, 1.0f, 0.0f }, 0.48, WHITE);
	EndMode3D();
}

void TableManager::DrawButtons()
{
	if (!this->m_SelectedElement.unlocked)
	{
		if (gameManager->GetBalance() >= this->m_SelectedElement.unlockPrice) {
			DrawTexture(this->UnlockButton, 1507, 927, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), { 1507, 927, (float)this->UnlockButton.width, (float)this->UnlockButton.height }))
			{
				DrawTexture(this->UnlockButtonHover, 1507, 927, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					int balance = gameManager->GetBalance();
					balance = balance - this->m_SelectedElement.unlockPrice;
					gameManager->SetBalance(balance);
					this->UnlockElement();
				}
			}
		}
		else {
			DrawTexture(this->UnlockButtonLocked, 1507, 927, WHITE);
		}
	}
	else
	{
		if (gameManager->GetBalance() >= this->m_SelectedElement.unitPrice) {

			DrawTexture(this->OrderButton, 1507, 927, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), { 1507, 927, (float)this->OrderButton.width, (float)this->OrderButton.height }))
			{
				DrawTexture(this->OrderButtonHover, 1507, 927, WHITE);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					// read savedata json
					Json::Value root;
					std::ifstream((gameManager->GetAssetPath() + "savedata.json").c_str()) >> root;
					for (int i = 0; i < root["inventory"].size(); i++)
					{
						if (root["inventory"][i]["name"].asCString() == this->m_SelectedElement.symbol)
						{
							root["inventory"][i]["quantity"] = root["inventory"][i]["quantity"].asInt() + 1;
							break;
						}
					}
					std::ofstream((gameManager->GetAssetPath() + "savedata.json").c_str()) << root;
					int balance = gameManager->GetBalance();
					balance = balance - this->m_SelectedElement.unitPrice;
					gameManager->SetBalance(balance);
				}
			}
		}
		else {
			DrawTexture(this->OrderButtonLocked, 1507, 927, WHITE);
		}
	}

}

void TableManager::UnlockElement() {
	Json::Value root;
	std::ifstream file((gameManager->GetAssetPath() + "elements/elements.json").c_str());
	file >> root;
	file.close();
	Json::Value inventory;
	std::ifstream file2((gameManager->GetAssetPath() + "savedata.json").c_str());
	file2 >> inventory;
	for (int i = 0; i < root["elements"].size(); i++) {
		if (root["elements"][i]["name"].asCString() == this->m_SelectedElement.name) {
			root["elements"][i]["unlocked"] = true;
			std::ofstream((gameManager->GetAssetPath() + "elements/elements.json").c_str()) << root;
			m_SelectedElement.unlocked = true;
			m_Elements[i].unlocked = true;
			Json::Value element;
			element["name"] = (this->m_SelectedElement.symbol).c_str();
			element["quantity"] = 0;
			inventory["inventory"].append(element);
			std::ofstream((gameManager->GetAssetPath() + "savedata.json").c_str()) << inventory;
			break;
		}
	}
}