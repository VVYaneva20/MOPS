#include <Game.hpp>

Game::Game() {
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png" }, { {0, 0} });
	gameManager->LoadButtons({ "Lab/PC.png" }, { "Lab/PCHover.png" }, { { 1580, 575 } });
	this->SetCameraSettings(this->camera);
	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();
		this->Update3D();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (gameManager->IsButtonClicked(0))
		{
			delete this;
			SiteHome* siteHome = new SiteHome();
			break;
		}
	}
}

void Game::SetCameraSettings(Camera &camera) {
	this->camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
	this->camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	this->camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	this->camera.fovy = 10.0f;
	this->camera.projection = CAMERA_PERSPECTIVE;
	SetCameraMode(this->camera, CAMERA_FREE);
}

void Game::Update3D() {
	UpdateCamera(&this->camera);
	this->model.transform = MatrixRotateXYZ(Vector3{ DEG2RAD * 1, DEG2RAD * yaw, DEG2RAD * 1 });
	this->camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
	this->yaw += 0.2f;
	
	BeginMode3D(this->camera);
	DrawModel(this->model, { 1.8f, 1.0f, 0.0f }, 0.5, WHITE);
	EndMode3D();
}

Game::~Game() {}